package app

func NewRenamer(
	fileLister FileLister,
	editor Editor,
	sanityChecker SanityChecker,
	filesystem Filesystem,
) *Renamer {
	return &Renamer{
		fileLister:    fileLister,
		editor:        editor,
		sanityChecker: sanityChecker,
		filesystem:    filesystem,
	}
}

type Renamer struct {
	fileLister    FileLister
	editor        Editor
	sanityChecker SanityChecker
	filesystem    Filesystem
}

func (r *Renamer) Rename(directory string) error {
	filenames, err := r.fileLister.ListFiles(directory)
	if err != nil {
		return err
	}

	newFilenames, err := r.editor.EditFilenames(filenames)
	if err != nil {
		return err
	}

	err = r.sanityChecker.Verify(filenames, newFilenames)
	if err != nil {
		return err
	}

	return r.filesystem.RenameFiles(directory, filenames, newFilenames)
}
