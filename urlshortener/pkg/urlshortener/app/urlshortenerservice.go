package app

import (
	"math/rand"

	"urlshortener/pkg/urlshortener/domain"
)

type URLShortenerService interface {
	AddURL(longURL string) (*domain.URL, error)
	GetURL(shortURL string) (*domain.URL, error)
}

func NewURLShortenerService(urlRepository URLRepository, urlConfiguration URLConfiguration) URLShortenerService {
	return &urlShortenerService{
		repository:    urlRepository,
		configuration: urlConfiguration,
	}
}

type urlShortenerService struct {
	repository    URLRepository
	configuration URLConfiguration
}

func (s *urlShortenerService) AddURL(longURL string) (*domain.URL, error) {
	shortURL := s.getShortURL(s.configuration.GetShortURLLength())
	url, err := s.repository.AddURL(shortURL, longURL)
	return url, err
}

func (s *urlShortenerService) GetURL(shortURL string) (*domain.URL, error) {
	url, err := s.repository.GetURL(shortURL)
	return url, err
}

func (s *urlShortenerService) getShortURL(length int) string {
	letters := []rune("abcdefghijklmnopqrstuvwxyz")
	b := make([]rune, length)
	for i := range b {
		b[i] = letters[rand.Intn(len(letters))]
	}
	return string(b)
}
