package app

import "errors"

var ErrTempDirectoryNotFound = errors.New("temp directory not found")

type Editor interface {
	EditFilenames(filenames []string) ([]string, error)
}
