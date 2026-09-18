package analysis

import (
	"io"

	"infosec/pkg/app"
)

func NewNarrowingAnalysisService() app.NarrowingAnalysisService {
	return &narrowingAnalysisService{}
}

type narrowingAnalysisService struct{}

func (s *narrowingAnalysisService) Analyze(in io.Reader) (app.PeriodicKey, error) {
	// TODO implement me
	panic("implement me")
}
