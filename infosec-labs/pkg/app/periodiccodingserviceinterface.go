package app

import "io"

type PeriodicKey = []byte

type PeriodicCodingServiceInterface interface {
	Encode(in io.Reader, out io.Writer, key PeriodicKey) error
	Decode(in io.Reader, out io.Writer, key PeriodicKey) error
}
