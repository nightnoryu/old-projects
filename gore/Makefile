all: modules test build lint

install: modules install-executable

modules:
	go mod tidy

test:
	go test ./...

build: build_dir
	go build -o bin/ .

build_dir:
	mkdir -p bin

lint:
	golangci-lint run

install-executable:
	go install .
