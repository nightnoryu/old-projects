package app

type FileLister interface {
	ListFiles(directory string) ([]string, error)
}
