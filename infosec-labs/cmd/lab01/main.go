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
				Usage: "encode a file with the provided key",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)
					outputFilename := ctx.Args().Get(1)
					key := ctx.Args().Get(2)

					return caesarCodingService.EncodePeriodic(inputFilename, outputFilename, []byte(key))
				},
			},
			{
				Name:  "decode",
				Usage: "decode a file with the provided key",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)
					outputFilename := ctx.Args().Get(1)
					key := ctx.Args().Get(2)

					return caesarCodingService.DecodePeriodic(inputFilename, outputFilename, []byte(key))
				},
			},
			{
				Name:  "analyze",
				Usage: "perform crypto-analysis on given file",
				Action: func(ctx *cli.Context) error {
					inputFilename := ctx.Args().Get(0)

					key, err := caesarCodingService.AnalyzePeriodic(inputFilename)
					if err != nil {
						return err
					}

					fmt.Printf("key: %s\n", string(key))
					return nil
				},
			},
		},
	}

	if err := application.Run(os.Args); err != nil {
		log.Fatal(err)
	}
}
