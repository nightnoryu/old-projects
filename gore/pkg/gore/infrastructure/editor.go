package infrastructure

import (
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"
	"time"

	"github.com/m3tro1d/gore/pkg/gore/app"
)

func NewEditor(editorExecutable string) app.Editor {
	return &editor{
		editorExecutable: editorExecutable,
	}
}

type editor struct {
	editorExecutable string
}

func (e *editor) EditFilenames(filenames []string) ([]string, error) {
	tempFilepath, err := e.getTempFilepath()
	if err != nil {
		return nil, err
	}

	err = e.dumpFilenames(tempFilepath, filenames)
	if err != nil {
		return nil, err
	}

	err = e.runEditor(tempFilepath)
	if err != nil {
		return nil, err
	}

	return e.readFilenames(tempFilepath)
}

func (e *editor) getTempFilepath() (string, error) {
	tempDirectory, found := os.LookupEnv("TEMP")
	if !found {
		return "", app.ErrTempDirectoryNotFound
	}

	tempFileName := e.generateTempFilename()

	return filepath.Join(tempDirectory, tempFileName), nil
}

func (e *editor) generateTempFilename() string {
	return "gore-tmp-" + strconv.FormatInt(time.Now().UnixNano(), 10) + ".txt"
}

func (e *editor) dumpFilenames(tempFilepath string, filenames []string) error {
	file, err := os.Create(tempFilepath)
	if err != nil {
		return err
	}
	//goland:noinspection GoUnhandledErrorResult
	defer file.Close()

	for _, filename := range filenames {
		_, err = file.WriteString(filename + "\n")
		if err != nil {
			return err
		}
	}

	return nil
}

func (e *editor) runEditor(tempFilepath string) error {
	// nolint: gosec
	cmd := exec.Command(e.editorExecutable, tempFilepath)
	cmd.Stdin, cmd.Stdout, cmd.Stderr = os.Stdin, os.Stdout, os.Stderr

	return cmd.Run()
}

func (e *editor) readFilenames(tempFilepath string) ([]string, error) {
	bytes, err := ioutil.ReadFile(tempFilepath)
	if err != nil {
		return nil, err
	}

	filenames := strings.Split(string(bytes), "\n")
	result := make([]string, 0, len(filenames))
	for _, filename := range filenames {
		if filename != "" {
			result = append(result, filename)
		}
	}

	return result, nil
}
