all: build
	./server
	rm server

build:
	g++ -o server src/server.cpp