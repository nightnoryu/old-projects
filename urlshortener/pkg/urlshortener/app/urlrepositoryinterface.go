package app

import "urlshortener/pkg/urlshortener/domain"

type URLRepository interface {
	AddURL(shortURL, longURL string) (*domain.URL, error)
	GetURL(shortURL string) (*domain.URL, error)
}
