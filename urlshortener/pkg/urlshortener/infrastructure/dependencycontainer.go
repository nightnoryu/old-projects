package infrastructure

import (
	"urlshortener/pkg/urlshortener/app"
	"urlshortener/pkg/urlshortener/handler"
)

type DependencyContainer interface {
	URLShortenerHandler() handler.URLShortenerHandler
}

func NewDependencyContainer() DependencyContainer {
	return &dependencyContainer{}
}

type dependencyContainer struct{}

func (container *dependencyContainer) URLShortenerHandler() handler.URLShortenerHandler {
	urlShortenerService := container.newURLShortenerService()
	return handler.NewURLShortenerHandler(urlShortenerService)
}

func (container *dependencyContainer) newURLShortenerService() app.URLShortenerService {
	repository := container.newURLShortenerRepository()
	configuration := container.newURLShortenerConfiguration()
	return app.NewURLShortenerService(repository, configuration)
}

func (container *dependencyContainer) newURLShortenerRepository() app.URLRepository {
	return NewURLRepository()
}

func (container *dependencyContainer) newURLShortenerConfiguration() app.URLConfiguration {
	return NewConstURLConfiguration()
}
