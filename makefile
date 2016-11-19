CC=g++

CFLAGS=-Wall -Werror -ansi -pedantic#-c not included here because it can't be used to run object files, a

all: main.o And.o Bar.o Commands.o Semi.o
	mkdir -p bin/
	$(CC) main.o And.o Bar.o Commands.o Semi.o -o bin/rshell

rshell: main.o And.o Bar.o Commands.o Semi.o
	mkdir -p bin/
	$(CC) main.o And.o Bar.o Commands.o Semi.o -o bin/rshell

main.o:
	$(CC) ./src/main.cpp $(CFLAGS) -c

And.o:
	$(CC) ./src/And.cpp $(CFLAGS) -c

Bar.o:
	$(CC) ./src/Bar.cpp $(CFLAGS) -c

Commands.o:
	$(CC) ./src/Commands.cpp $(CFLAGS) -c

Semi.o:
	$(CC) ./src/Semi.cpp $(CFLAGS) -c

Pound.o:
	$(CC) ./src/Pound.cpp $(CFLAGS) -c

clean:
	rm -r bin
	rm -r *.o