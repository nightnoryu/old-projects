package test

import (
	"errors"
	"testing"

	"urlshortener/pkg/urlshortener/app"
	"urlshortener/pkg/urlshortener/domain"

	"github.com/stretchr/testify/assert"
)

func TestURLShortenerService_AddURl(t *testing.T) {
	longURL := "https://github.com/whatever"
	shortURlLength := 10

	repo := newMockURLRepository()
	config := newMockURLConfiguration(shortURlLength)
	urlShortenerService := app.NewURLShortenerService(repo, config)

	url, err := urlShortenerService.AddURL(longURL)
	assert.Nil(t, err)
	assert.True(t, url.Expanded() == longURL, "longURL")
	assert.True(t, len(url.Short()) == shortURlLength, "shortURLLength")

	url1, err := urlShortenerService.GetURL(url.Short())
	assert.Nil(t, err)
	assert.True(t, url1.Expanded() == longURL, "longURL")
	assert.True(t, len(url1.Short()) == shortURlLength, "shortURLLength")
	assert.True(t, url1.Short() == url.Short(), "shortURL")

	_, err = urlShortenerService.GetURL("non-existent")
	assert.Error(t, err, "non-existent URl error")
}

func newMockURLRepository() app.URLRepository {
	return &mockURLRepository{
		data: make(map[string]string),
	}
}

type mockURLRepository struct {
	data map[string]string
}

func (r *mockURLRepository) AddURL(shortURL, longURL string) (*domain.URL, error) {
	r.data[shortURL] = longURL
	return domain.NewURL(shortURL, longURL), nil
}

func (r *mockURLRepository) GetURL(shortURL string) (*domain.URL, error) {
	longURL, ok := r.data[shortURL]
	if !ok {
		return nil, errors.New("url not found")
	}
	return domain.NewURL(shortURL, longURL), nil
}

func newMockURLConfiguration(shortURLLength int) app.URLConfiguration {
	return &mockURlConfiguration{ShortURLLength: shortURLLength}
}

type mockURlConfiguration struct {
	ShortURLLength int
}

func (c *mockURlConfiguration) GetShortURLLength() int {
	return c.ShortURLLength
}
