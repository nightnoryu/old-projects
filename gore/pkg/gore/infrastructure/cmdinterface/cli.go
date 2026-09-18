package cmdinterface

import (
	"context"

	"github.com/urfave/cli/v2"
)

const (
	programName    = "gore"
	programUsage   = "bulk rename utility"
	programVersion = "v0.2.2"

	versionFlag      = "version"
	versionFlagAlias = "v"
	versionFlagUsage = "print program version"

	directoryFlag            = "directory"
	directoryFlagAlias       = "d"
	directoryFlagUsage       = "directory to rename files in"
	directoryFlagDefault     = "."
	directoryFlagDefaultText = "current"

	editorFlag        = "editor"
	editorFlagAlias   = "e"
	editorFlagUsage   = "editor to use"
	editorFlagDefault = "nvim"
)

type MainFunc = func(ctx context.Context) error

func InitializeApplication(main MainFunc) *cli.App {
	cli.VersionFlag = &cli.BoolFlag{
		Name:    versionFlag,
		Aliases: []string{versionFlagAlias},
		Usage:   versionFlagUsage,
	}

	return &cli.App{
		Name:    programName,
		Usage:   programUsage,
		Version: programVersion,

		Flags:  initializeFlags(),
		Action: initializeAction(main),
	}
}

func initializeFlags() []cli.Flag {
	return []cli.Flag{
		&cli.StringFlag{
			Name:        directoryFlag,
			Aliases:     []string{directoryFlagAlias},
			Usage:       directoryFlagUsage,
			DefaultText: directoryFlagDefaultText,
			Value:       directoryFlagDefault,
		},
		&cli.StringFlag{
			Name:        editorFlag,
			Aliases:     []string{editorFlagAlias},
			Usage:       editorFlagUsage,
			DefaultText: editorFlagDefault,
			Value:       editorFlagDefault,
		},
	}
}

func initializeAction(main MainFunc) cli.ActionFunc {
	return func(ctx *cli.Context) error {
		editor := ctx.String(editorFlag)
		directory := ctx.String(directoryFlag)

		mainCtx := newArgumentsContext(
			context.Background(),
			&Arguments{
				Editor:    editor,
				Directory: directory,
			})

		return main(mainCtx)
	}
}
