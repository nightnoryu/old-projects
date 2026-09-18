package cmdinterface

import (
	"context"
	"errors"
)

var ErrNoArgumentsProvided = errors.New("no arguments provided")

type key int

// nolint: gochecknoglobals
var argumentsKey key

type Arguments struct {
	Editor    string
	Directory string
}

func newArgumentsContext(ctx context.Context, arguments *Arguments) context.Context {
	return context.WithValue(ctx, argumentsKey, arguments)
}

func ArgumentsFromContext(ctx context.Context) (*Arguments, error) {
	arguments, ok := ctx.Value(argumentsKey).(*Arguments)
	if !ok {
		return nil, ErrNoArgumentsProvided
	}

	return arguments, nil
}
