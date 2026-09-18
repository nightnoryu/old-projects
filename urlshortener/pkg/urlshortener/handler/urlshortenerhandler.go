package handler

import (
	"encoding/json"
	"fmt"
	"net/http"

	"urlshortener/pkg/urlshortener/app"
	"urlshortener/pkg/urlshortener/domain"

	"github.com/gorilla/mux"
)

type URLShortenerHandler interface {
	Save(w http.ResponseWriter, r *http.Request)
	Expand(w http.ResponseWriter, r *http.Request)
	Resolve(w http.ResponseWriter, r *http.Request)
}

func NewURLShortenerHandler(urlShortenerService app.URLShortenerService) URLShortenerHandler {
	return &urlShortenerHandler{
		service: urlShortenerService,
	}
}

type urlShortenerHandler struct {
	service app.URLShortenerService
}

func (h *urlShortenerHandler) Save(w http.ResponseWriter, r *http.Request) {
	var request struct {
		URL string `json:"url"`
	}
	err := json.NewDecoder(r.Body).Decode(&request)
	if err != nil {
		h.errorResponse(w, "Please include 'url' parameter", http.StatusBadRequest)
		return
	}

	url, err := h.service.AddURL(request.URL)
	if err != nil {
		h.errorResponse(w, fmt.Sprintf("Error while saving URL: %v", err), http.StatusBadRequest)
		return
	}

	err = h.jsonResponse(w, url, http.StatusCreated)
	if err != nil {
		h.errorResponse(w, "Error while encoding URL", http.StatusInternalServerError)
	}
}

func (h *urlShortenerHandler) Expand(w http.ResponseWriter, r *http.Request) {
	shortURL := mux.Vars(r)["url"]
	url, err := h.service.GetURL(shortURL)
	if err != nil {
		h.errorResponse(w, fmt.Sprintf("Error while resolving URL: %v", err), http.StatusNotFound)
		return
	}

	err = h.jsonResponse(w, url, http.StatusOK)
	if err != nil {
		h.errorResponse(w, "Error while encoding URL", http.StatusInternalServerError)
	}
}

func (h *urlShortenerHandler) Resolve(w http.ResponseWriter, r *http.Request) {
	shortURL := mux.Vars(r)["url"]
	url, err := h.service.GetURL(shortURL)
	if err != nil {
		h.errorResponse(w, fmt.Sprintf("Error while resolving URL: %v", err), http.StatusNotFound)
		return
	}

	http.Redirect(w, r, url.Expanded(), http.StatusFound)
}

func (h *urlShortenerHandler) jsonResponse(w http.ResponseWriter, url *domain.URL, statusCode int) error {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(statusCode)
	err := json.NewEncoder(w).Encode(url)
	return err
}

func (h *urlShortenerHandler) errorResponse(w http.ResponseWriter, msg string, statusCode int) {
	w.WriteHeader(statusCode)
	_, err := fmt.Fprintln(w, msg)
	if err != nil {
		fmt.Println("Error while writing response")
	}
}
