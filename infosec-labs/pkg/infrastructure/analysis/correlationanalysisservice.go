package analysis

import (
	"io"

	"infosec/pkg/app"
)

func NewCorrelationAnalysisService() app.CorrelationAnalysisService {
	return &correlationAnalysisService{}
}

type correlationAnalysisService struct{}

func (s *correlationAnalysisService) Analyze(in io.Reader) (app.SequentialKey, error) {
	// TODO implement me
	panic("implement me")
}
