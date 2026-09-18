package infrastructure

import (
	"database/sql"
	"errors"
	"log"
	"os"
	"time"

	"urlshortener/pkg/urlshortener/domain"

	_ "github.com/go-sql-driver/mysql"
)

const addQuery = "INSERT INTO url (short, expanded) VALUES (?, ?)"
const getQuery = "SELECT short, expanded FROM url WHERE short = ?"

func NewURLRepository() *urlRepository {
	db, err := sql.Open("mysql", os.Getenv("DATABASE_URL"))
	if err != nil {
		log.Fatal(err)
	}
	db.SetConnMaxLifetime(time.Minute * 3)
	db.SetMaxOpenConns(10)
	db.SetMaxIdleConns(10)
	return &urlRepository{
		db: db,
	}
}

type urlRepository struct {
	db *sql.DB
}

func (r *urlRepository) AddURL(shortURL, longURL string) (*domain.URL, error) {
	stmt, err := r.db.Prepare(addQuery)
	if err != nil {
		return nil, err
	}

	defer stmt.Close()

	_, err = stmt.Exec(shortURL, longURL)
	if err != nil {
		return nil, err
	}

	return domain.NewURL(shortURL, longURL), nil
}

func (r *urlRepository) GetURL(shortURL string) (*domain.URL, error) {
	stmt, err := r.db.Prepare(getQuery)
	if err != nil {
		return nil, err
	}
	defer stmt.Close()

	row := stmt.QueryRow(shortURL)
	var short, expanded string
	err = row.Scan(&short, &expanded)
	if err != nil {
		return nil, errors.New("URL not found")
	}

	url := domain.NewURL(short, expanded)
	return url, nil
}
