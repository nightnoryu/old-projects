package main

import (
	"fmt"
	"log"
	"os"

	"infosec/pkg/infrastructure"

	"github.com/urfave/cli/v2"
)

func main() {
	dependencyContainer := infrastructure.NewDependencyContainer()
	caesarCodingService := dependencyContainer.CaesarCodingService()

	application := &cli.App{
		Commands: []*cli.Command{
			{
				Name:  "encode",
				Usage: "encode a file generating a key in the process",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)
					outputFilename := ctx.Args().Get(1)
					keyFilename := ctx.Args().Get(2)

					return caesarCodingService.EncodeSequential(inputFilename, outputFilename, keyFilename)
				},
			},
			{
				Name:  "decode",
				Usage: "decode a file with the provided key",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)
					outputFilename := ctx.Args().Get(1)
					keyFilename := ctx.Args().Get(2)

					return caesarCodingService.DecodeSequential(inputFilename, outputFilename, keyFilename)
				},
			},
			{
				Name:  "analyze",
				Usage: "perform crypto-analysis on given file",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)
					keyFilename := ctx.Args().Get(1)

					err := caesarCodingService.AnalyzeSequential(inputFilename, keyFilename)
					if err != nil {
						return err
					}

					fmt.Printf("key saved to '%s'\n", keyFilename)
					return nil
				},
			},
		},
	}

	if err := application.Run(os.Args); err != nil {
		log.Fatal(err)
	}
}
