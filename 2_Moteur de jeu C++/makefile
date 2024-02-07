CC = g++
CFLAGS = -std=c++11

all: GobletGobblers

GobletGobblers: main.o board.o
	$(CC) $(CFLAGS) -o GobletGobblers main.o board.o

main.o: main.cpp board.h
	$(CC) $(CFLAGS) -c main.cpp

board.o: board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp

clean:
	rm -f *.o GobletGobblers
