package infrastructure

import (
	"infosec/pkg/app"
	"infosec/pkg/infrastructure/analysis"
	"infosec/pkg/infrastructure/coding"
	"infosec/pkg/infrastructure/generator"
)

type DependencyContainer interface {
	CaesarCodingService() app.CaesarCodingService
}

func NewDependencyContainer() DependencyContainer {
	numberGenerator := generator.NewNumberGenerator()

	periodicCodingService := coding.NewPeriodicCodingService()
	sequentialCodingService := coding.NewSequentialCodingService(numberGenerator)

	narrowingAnalysisService := analysis.NewNarrowingAnalysisService()
	correlationAnalysisService := analysis.NewCorrelationAnalysisService()

	caesarCodingService := app.NewCaesarCodingService(
		periodicCodingService,
		sequentialCodingService,
		narrowingAnalysisService,
		correlationAnalysisService,
	)

	return &dependencyContainer{
		caesarCodingService: caesarCodingService,
	}
}

type dependencyContainer struct {
	caesarCodingService app.CaesarCodingService
}

func (container *dependencyContainer) CaesarCodingService() app.CaesarCodingService {
	return container.caesarCodingService
}
