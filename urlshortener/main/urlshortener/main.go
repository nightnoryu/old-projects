package main

import (
	"log"
	"math/rand"
	"net/http"
	"time"

	"urlshortener/pkg/urlshortener/infrastructure"

	"github.com/gorilla/mux"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	r := initializeRouter()
	http.Handle("/", r)
	log.Fatal(http.ListenAndServe(":8080", nil))
}

func initializeRouter() *mux.Router {
	r := mux.NewRouter()
	shortenerHandler := infrastructure.NewDependencyContainer().URLShortenerHandler()

	r.HandleFunc("/save", shortenerHandler.Save).Methods("POST")
	r.HandleFunc("/expand/{url:[a-z]+}", shortenerHandler.Expand).Methods("GET")
	r.HandleFunc("/resolve/{url:[a-z]+}", shortenerHandler.Resolve).Methods("GET")
	r.Use(loggingMiddleware)

	return r
}

func loggingMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		log.Println("http:", r.Method, r.URL.Path, r.RemoteAddr, r.UserAgent())
		next.ServeHTTP(w, r)
	})
}
