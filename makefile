
SRC = graph.cpp main.cpp ismorphism.cpp tree.cpp
OBJECTS = graph.o main.o ismorphism.o tree.o
HEADERS = graph.h queue.h tree.h ismorphism.h bucketsort.h
BIN = graphIsomorph.out
PRODBIN = prodIsomorph.out

CC = g++
CFLAGS = -g -Wall -fsanitize=address -std=c++17

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

.PHONY: clean
clean:
	rm -rf $(BIN) $(OBJECTS)

.PHONEY: production
production:
	$(CC) -std=c++17 -o $(PRODBIN) $(SRC)