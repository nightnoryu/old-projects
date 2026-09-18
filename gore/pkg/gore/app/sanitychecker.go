package app

import "errors"

var ErrFileAmountsDoNotMatch = errors.New("file amounts do not match")

type SanityChecker interface {
	Verify(filesBefore, filesAfter []string) error
}

func NewSanityChecker() SanityChecker {
	return &sanityChecker{}
}

type sanityChecker struct{}

func (c *sanityChecker) Verify(filesBefore, filesAfter []string) error {
	if len(filesBefore) != len(filesAfter) {
		return ErrFileAmountsDoNotMatch
	}

	return nil
}
