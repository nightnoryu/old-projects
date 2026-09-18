package coding

import (
	stderrors "errors"
	"io"

	"infosec/pkg/app"
	"infosec/pkg/infrastructure/generator"

	"github.com/pkg/errors"
)

const k = 42

var ErrKeyTooShort = stderrors.New("key too short")

func NewSequentialCodingService(numberGenerator *generator.NumberGenerator) app.SequentialCodingServiceInterface {
	return &sequentialCodingService{
		numberGenerator: numberGenerator,
	}
}

type sequentialCodingService struct {
	numberGenerator    *generator.NumberGenerator
	currentKey         app.SequentialKey
	currentKeyPosition int
}

func (s *sequentialCodingService) Encode(in io.Reader, out io.Writer) (app.SequentialKey, error) {
	s.performNumberGeneratorDryRuns()

	buf := make([]byte, bufferSize)
	s.currentKey = make(app.SequentialKey, 0, bufferSize)

	for {
		numberRead, err := in.Read(buf)
		if stderrors.Is(err, io.EOF) {
			break
		} else if err != nil {
			return nil, errors.WithStack(err)
		}

		if numberRead > 0 {
			result := s.encodeBufferAndPopulateKey(buf, numberRead)
			_, err := out.Write(result[0:numberRead])
			if err != nil {
				return nil, errors.WithStack(err)
			}
		}
	}

	return s.currentKey, nil
}

func (s *sequentialCodingService) Decode(in io.Reader, out io.Writer, key app.SequentialKey) error {
	buf := make([]byte, bufferSize)
	s.currentKeyPosition = 0

	for {
		numberRead, err := in.Read(buf)
		if stderrors.Is(err, io.EOF) {
			break
		} else if err != nil {
			return errors.WithStack(err)
		}

		if numberRead > 0 {
			result, err := s.decodeBufferWithSequentialKey(buf, numberRead, key)
			if err != nil {
				return err
			}

			_, err = out.Write(result[0:numberRead])
			if err != nil {
				return errors.WithStack(err)
			}
		}
	}

	return nil
}

func (s *sequentialCodingService) encodeBufferAndPopulateKey(buf []byte, numberRead int) []byte {
	result := make([]byte, 0, len(buf))
	for i, character := range buf {
		if i == numberRead {
			break
		}

		keyCharacter := byte(s.numberGenerator.GenerateNext() % 256)
		s.currentKey = append(s.currentKey, keyCharacter)
		result = append(result, character+keyCharacter)
	}

	return result
}

func (s *sequentialCodingService) decodeBufferWithSequentialKey(buf []byte, numberRead int, key app.SequentialKey) ([]byte, error) {
	result := make([]byte, 0, len(buf))
	for i, character := range buf {
		if i == numberRead {
			break
		}

		if s.currentKeyPosition >= len(key) {
			return nil, errors.WithStack(ErrKeyTooShort)
		}

		keyCharacter := key[s.currentKeyPosition]
		s.currentKeyPosition++
		result = append(result, character-keyCharacter)
	}

	return result, nil
}

func (s *sequentialCodingService) performNumberGeneratorDryRuns() {
	for i := 0; i < k; i++ {
		s.numberGenerator.GenerateNext()
	}
}
