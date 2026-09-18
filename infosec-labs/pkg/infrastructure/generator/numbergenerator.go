package generator

const (
	m = 1406986169
	a = 705009367
	c = 1052759843
)

func NewNumberGenerator() *NumberGenerator {
	return &NumberGenerator{}
}

type NumberGenerator struct {
	previousValue int
}

func (g *NumberGenerator) GenerateNext() int {
	nextValue := (a*g.previousValue + c) % m
	g.previousValue = nextValue
	return nextValue
}
