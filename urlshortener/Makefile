all: build format test lint

build: modules
	go build -o ./bin/urlshortener.exe ./main/urlshortener/.

modules:
	go mod tidy

lint:
	golangci-lint run ./...

format:
	go fmt ./...

test:
	go test ./...

clean:
	rm -r ./bin
