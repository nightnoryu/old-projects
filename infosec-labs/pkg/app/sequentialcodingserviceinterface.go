package app

import "io"

type SequentialKey = []byte

type SequentialCodingServiceInterface interface {
	Encode(in io.Reader, out io.Writer) (SequentialKey, error)
	Decode(in io.Reader, out io.Writer, key SequentialKey) error
}
