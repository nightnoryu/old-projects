package infrastructure

func NewConstURLConfiguration() *constURLConfiguration {
	return &constURLConfiguration{
		shortUrlLength: 8,
	}
}

type constURLConfiguration struct {
	shortUrlLength int
}

func (c constURLConfiguration) GetShortURLLength() int {
	return c.shortUrlLength
}
