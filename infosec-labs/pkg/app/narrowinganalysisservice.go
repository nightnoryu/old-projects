package app

import "io"

type NarrowingAnalysisService interface {
	Analyze(in io.Reader) (PeriodicKey, error)
}
