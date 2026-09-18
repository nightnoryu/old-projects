package main

import (
	"context"
	"log"
	"os"

	"github.com/m3tro1d/gore/pkg/gore/app"
	"github.com/m3tro1d/gore/pkg/gore/infrastructure"
	"github.com/m3tro1d/gore/pkg/gore/infrastructure/cmdinterface"
)

func main() {
	application := cmdinterface.InitializeApplication(func(ctx context.Context) error {
		arguments, err := cmdinterface.ArgumentsFromContext(ctx)
		if err != nil {
			return err
		}

		renamer := app.NewRenamer(
			infrastructure.NewFileLister(),
			infrastructure.NewEditor(arguments.Editor),
			app.NewSanityChecker(),
			infrastructure.NewFilesystem(),
		)

		return renamer.Rename(arguments.Directory)
	})

	if err := application.Run(os.Args); err != nil {
		log.Fatal(err)
	}
}
