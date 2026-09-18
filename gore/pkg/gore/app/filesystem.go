package app

type Filesystem interface {
	RenameFiles(directory string, filenames, newFilenames []string) error
}
