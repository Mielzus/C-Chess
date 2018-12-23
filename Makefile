CC=g++
CFLAGS=-Wall -std=c++11

chess: build/main.o build/board.o build/square.o build/piece.o build/player.o build/colour.o
	$(CC) $(CFLAGS) -o bin/chess build/main.o build/board.o build/square.o build/piece.o build/player.o build/colour.o

build/main.o: src/main.cc
	$(CC) $(CFLAGS) -c src/main.cc -o build/main.o

build/board.o: src/chess/board.cc
	$(CC) $(CFLAGS) -c src/chess/board.cc -o build/board.o

build/square.o: src/chess/square.cc
	$(CC) $(CFLAGS) -c src/chess/square.cc -o build/square.o

build/piece.o: src/chess/piece.cc
	$(CC) $(CFLAGS) -c src/chess/piece.cc -o build/piece.o

build/player.o: src/chess/player.cc
	$(CC) $(CFLAGS) -c src/chess/player.cc -o build/player.o

build/colour.o: src/chess/colour.cc
	$(CC) $(CFLAGS) -c src/chess/colour.cc -o build/colour.o

clean:
	rm -f build/*.o
	rm -f bin/chess
	make chess

run:
	./bin/chess