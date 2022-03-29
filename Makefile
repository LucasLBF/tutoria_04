CC=g++
FLAGS=-c -o

all: process roundrobin bin

process: process.cpp
	$(CC) $< $(FLAGS) $@

roundrobin: roundRobin.cpp
	$(CC) $< $(FLAGS) $@

bin: main.cpp
	$(CC) $< $(FLAGS) $@

.PHONY: run clean

run: 
	./bin

clean:
	rm bin process roundrobin
