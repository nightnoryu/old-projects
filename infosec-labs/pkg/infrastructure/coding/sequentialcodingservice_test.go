package coding

import (
	stderrors "errors"
	"strings"
	"testing"

	"infosec/pkg/infrastructure/generator"

	"github.com/stretchr/testify/assert"
)

const initialToughMessage = "Her name was Lola 🙍 She was a showgirl 💃\n\rИ что-то на русском"

func TestSequentialCodingService_EncodeAndDecodeWithGeneratedKey(t *testing.T) {
	service := NewSequentialCodingService(generator.NewNumberGenerator())

	in := strings.NewReader(initialToughMessage)
	out := new(strings.Builder)

	key, err := service.Encode(in, out)

	assert.Nil(t, err)
	assert.NotEqual(t, initialToughMessage, out.String())
	assert.Len(t, key, len(initialToughMessage))

	in = strings.NewReader(out.String())
	out = new(strings.Builder)

	err = service.Decode(in, out, key)

	assert.Nil(t, err)
	assert.Equal(t, out.String(), initialToughMessage)
}

func TestSequentialCodingService_EncodeAndDecodeWithDistinctKeys(t *testing.T) {
	service := NewSequentialCodingService(generator.NewNumberGenerator())

	in := strings.NewReader(initialToughMessage)
	out := new(strings.Builder)

	key, err := service.Encode(in, out)

	assert.Nil(t, err)
	assert.NotEqual(t, initialToughMessage, out.String())

	in = strings.NewReader(out.String())
	out = new(strings.Builder)
	key[5] = 6
	key[9] = 9

	err = service.Decode(in, out, key)

	assert.Nil(t, err)
	assert.NotEqual(t, out.String(), initialToughMessage)
}

func TestSequentialCodingService_EncodeAndDecodeWithKeyShorterThanInitialMessage(t *testing.T) {
	service := NewSequentialCodingService(generator.NewNumberGenerator())

	in := strings.NewReader(initialToughMessage)
	out := new(strings.Builder)

	key, err := service.Encode(in, out)

	assert.Nil(t, err)
	assert.NotEqual(t, initialToughMessage, out.String())

	in = strings.NewReader(out.String())
	out = new(strings.Builder)
	key = key[0 : len(key)-1]

	err = service.Decode(in, out, key)

	assert.True(t, stderrors.Is(err, ErrKeyTooShort))
}
