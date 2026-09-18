package coding

import (
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

const initialMessage = "Every now and then I get\n\rA little bit lonely..."

func TestPeriodicCodingService_EncodeAndDecodeWithTheSameKey(t *testing.T) {
	service := NewPeriodicCodingService()

	in := strings.NewReader(initialMessage)
	out := new(strings.Builder)
	key := []byte{'1', '2', '3'}

	err := service.Encode(in, out, key)

	assert.Nil(t, err)
	assert.NotEqual(t, initialMessage, out.String())

	in = strings.NewReader(out.String())
	out = new(strings.Builder)

	err = service.Decode(in, out, key)

	assert.Nil(t, err)
	assert.Equal(t, out.String(), initialMessage)
}

func TestPeriodicCodingService_EncodeAndDecodeWithDistinctKeys(t *testing.T) {
	service := NewPeriodicCodingService()

	in := strings.NewReader(initialMessage)
	out := new(strings.Builder)
	key := []byte{'1', '2', '3'}

	err := service.Encode(in, out, key)

	assert.Nil(t, err)
	assert.NotEqual(t, initialMessage, out.String())

	in = strings.NewReader(out.String())
	out = new(strings.Builder)
	newKey := []byte{'a', 'b'}

	err = service.Decode(in, out, newKey)

	assert.Nil(t, err)
	assert.NotEqual(t, out.String(), initialMessage)
}
