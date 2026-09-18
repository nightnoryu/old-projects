package infrastructure

import (
	"os"

	"github.com/m3tro1d/gore/pkg/gore/app"
)

func NewFileLister() app.FileLister {
	return &fileLister{}
}

type fileLister struct{}

func (l *fileLister) ListFiles(directory string) ([]string, error) {
	entries, err := os.ReadDir(directory)
	if err != nil {
		return nil, err
	}

	result := make([]string, 0, len(entries))
	for _, entry := range entries {
		if !entry.IsDir() {
			result = append(result, entry.Name())
		}
	}

	return result, nil
}
