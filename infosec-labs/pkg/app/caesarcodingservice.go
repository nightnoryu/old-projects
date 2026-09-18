package app

import (
	"os"

	"github.com/pkg/errors"
)

type CaesarCodingService interface {
	EncodePeriodic(inputFilename, outputFilename string, key PeriodicKey) error
	DecodePeriodic(inputFilename, outputFilename string, key PeriodicKey) error
	AnalyzePeriodic(inputFilename string) (PeriodicKey, error)

	EncodeSequential(inputFilename, outputFilename, keyFilename string) error
	DecodeSequential(inputFilename, outputFilename string, keyFilename string) error
	AnalyzeSequential(inputFilename, keyFilename string) error
}

func NewCaesarCodingService(
	periodicCodingService PeriodicCodingServiceInterface,
	sequentialCodingService SequentialCodingServiceInterface,
	narrowingAnalysisService NarrowingAnalysisService,
	correlationAnalysisService CorrelationAnalysisService,
) CaesarCodingService {
	return &caesarCodingService{
		periodicCodingService:      periodicCodingService,
		sequentialCodingService:    sequentialCodingService,
		narrowingAnalysisService:   narrowingAnalysisService,
		correlationAnalysisService: correlationAnalysisService,
	}
}

type caesarCodingService struct {
	periodicCodingService      PeriodicCodingServiceInterface
	sequentialCodingService    SequentialCodingServiceInterface
	narrowingAnalysisService   NarrowingAnalysisService
	correlationAnalysisService CorrelationAnalysisService
}

func (s *caesarCodingService) EncodePeriodic(inputFilename, outputFilename string, key PeriodicKey) error {
	in, out, err := openInputAndOutputFiles(inputFilename, outputFilename)
	if err != nil {
		return err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()
	// noinspection GoUnhandledErrorResult
	defer out.Close()

	return s.periodicCodingService.Encode(in, out, key)
}

func (s *caesarCodingService) DecodePeriodic(inputFilename, outputFilename string, key PeriodicKey) error {
	in, out, err := openInputAndOutputFiles(inputFilename, outputFilename)
	if err != nil {
		return err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()
	// noinspection GoUnhandledErrorResult
	defer out.Close()

	return s.periodicCodingService.Decode(in, out, key)
}

func (s *caesarCodingService) AnalyzePeriodic(inputFilename string) (PeriodicKey, error) {
	in, err := openInputFile(inputFilename)
	if err != nil {
		return nil, err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()

	return s.narrowingAnalysisService.Analyze(in)
}

func (s *caesarCodingService) EncodeSequential(inputFilename, outputFilename, keyFilename string) error {
	in, out, err := openInputAndOutputFiles(inputFilename, outputFilename)
	if err != nil {
		return err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()
	// noinspection GoUnhandledErrorResult
	defer out.Close()

	key, err := s.sequentialCodingService.Encode(in, out)
	if err != nil {
		return err
	}

	return saveSequentialKeyToFile(key, keyFilename)
}

func (s *caesarCodingService) DecodeSequential(inputFilename, outputFilename, keyFilename string) error {
	in, out, err := openInputAndOutputFiles(inputFilename, outputFilename)
	if err != nil {
		return err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()
	// noinspection GoUnhandledErrorResult
	defer out.Close()

	key, err := readSequentialKeyFromFile(keyFilename)
	if err != nil {
		return err
	}

	return s.sequentialCodingService.Decode(in, out, key)
}

func (s *caesarCodingService) AnalyzeSequential(inputFilename, keyFilename string) error {
	in, err := openInputFile(inputFilename)
	if err != nil {
		return err
	}
	// noinspection GoUnhandledErrorResult
	defer in.Close()

	key, err := s.correlationAnalysisService.Analyze(in)
	if err != nil {
		return err
	}

	return saveSequentialKeyToFile(key, keyFilename)
}

func openInputAndOutputFiles(inputFilename, outputFilename string) (in, out *os.File, err error) {
	in, err = os.Open(inputFilename)
	if err != nil {
		return nil, nil, errors.WithStack(errors.Wrap(err, "failed to open file for reading"))
	}

	out, err = os.Create(outputFilename)
	if err != nil {
		return nil, nil, errors.WithStack(errors.Wrap(err, "failed to open file for writing"))
	}

	return in, out, nil
}

func openInputFile(filename string) (*os.File, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, errors.WithStack(errors.Wrap(err, "failed to open file for reading"))
	}
	return file, nil
}

func saveSequentialKeyToFile(key SequentialKey, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return errors.WithStack(errors.Wrap(err, "failed to open file for writing"))
	}
	// noinspection GoUnhandledErrorResult
	defer file.Close()

	_, err = file.Write(key)
	return errors.WithStack(err)
}

func readSequentialKeyFromFile(filename string) (SequentialKey, error) {
	key, err := os.ReadFile(filename)
	return key, errors.WithStack(err)
}
