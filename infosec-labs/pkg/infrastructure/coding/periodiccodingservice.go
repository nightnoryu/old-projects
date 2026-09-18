package coding

import (
	stderrors "errors"
	"io"

	"infosec/pkg/app"

	"github.com/pkg/errors"
)

const bufferSize = 1024

func NewPeriodicCodingService() app.PeriodicCodingServiceInterface {
	return &periodicCodingService{}
}

type periodicCodingService struct{}

func (s *periodicCodingService) Encode(in io.Reader, out io.Writer, key app.PeriodicKey) error {
	buf := make([]byte, bufferSize)
	for {
		numberRead, err := in.Read(buf)
		if stderrors.Is(err, io.EOF) {
			break
		} else if err != nil {
			return errors.WithStack(err)
		}

		if numberRead > 0 {
			result := encodeBufferWithPeriodicKey(buf, numberRead, key)
			_, err := out.Write(result[0:numberRead])
			if err != nil {
				return errors.WithStack(err)
			}
		}
	}

	return nil
}

func (s *periodicCodingService) Decode(in io.Reader, out io.Writer, key app.PeriodicKey) error {
	buf := make([]byte, bufferSize)
	for {
		numberRead, err := in.Read(buf)
		if stderrors.Is(err, io.EOF) {
			break
		} else if err != nil {
			return errors.WithStack(err)
		}

		if numberRead > 0 {
			result := decodeBufferWithPeriodicKey(buf, numberRead, key)
			_, err := out.Write(result[0:numberRead])
			if err != nil {
				return errors.WithStack(err)
			}
		}
	}

	return nil
}

func encodeBufferWithPeriodicKey(buf []byte, numberRead int, key app.PeriodicKey) []byte {
	result := make([]byte, 0, len(buf))
	for i, character := range buf {
		if i == numberRead {
			break
		}

		keyCharacter := key[i%len(key)]
		result = append(result, character+keyCharacter)
	}

	return result
}

func decodeBufferWithPeriodicKey(buf []byte, numberRead int, key app.PeriodicKey) []byte {
	result := make([]byte, 0, len(buf))
	for i, character := range buf {
		if i == numberRead {
			break
		}

		keyCharacter := key[i%len(key)]
		result = append(result, character-keyCharacter)
	}

	return result
}
