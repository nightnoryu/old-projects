package app

import "io"

type CorrelationAnalysisService interface {
	Analyze(in io.Reader) (SequentialKey, error)
}
