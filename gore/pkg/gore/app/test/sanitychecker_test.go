package test

import (
	"testing"

	"github.com/stretchr/testify/assert"

	"github.com/m3tro1d/gore/pkg/gore/app"
)

func TestSanityChecker_EqualFileListLengthsShouldWorkFine(t *testing.T) {
	t.Parallel()
	sanityChecker := app.NewSanityChecker()

	filesBefore := []string{
		"test1.txt",
		"test2.txt",
	}
	filesAfter := []string{
		"renamed1.txt",
		"renamed2.txt",
	}

	err := sanityChecker.Verify(filesBefore, filesAfter)
	assert.Nil(t, err)
}

func TestSanityChecker_DifferentFileListLengthsShouldReturnError(t *testing.T) {
	t.Parallel()
	sanityChecker := app.NewSanityChecker()

	filesBefore := []string{
		"test1.txt",
		"test2.txt",
	}
	filesAfter := []string{
		"renamed1.txt",
	}

	err := sanityChecker.Verify(filesBefore, filesAfter)
	assert.ErrorIs(t, err, app.ErrFileAmountsDoNotMatch)

	filesAfter = []string{
		"renamed1.txt",
		"renamed2.txt",
		"renamed3.txt",
	}

	err = sanityChecker.Verify(filesBefore, filesAfter)
	assert.ErrorIs(t, err, app.ErrFileAmountsDoNotMatch)
}
