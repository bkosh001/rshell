CC=g++

CFLAGS=-Wall -Werror -ansi -pedantic#-c not included here because it can't be used to run object files

all: main.o And.o Bar.o Commands.o Semi.o Pound.o
	mkdir -p bin/
	$(CC) main.o And.o Bar.o Commands.o Semi.o Pound.o -o bin/rshell

main.o: main.cpp Commands.h And.h Bar.h Semi.h Shell.h Pound.h
	$(CC) main.cpp $(CFLAGS) -c

And.o: And.cpp And.h Symbols.h Shell.h
	$(CC) And.cpp $(CFLAGS) -c

Bar.o: Bar.cpp Bar.h Symbols.h Shell.h
	$(CC) Bar.cpp $(CFLAGS) -c
    
Commands.o: Commands.cpp Commands.h Shell.h
	$(CC) Commands.cpp $(CFLAGS) -c
	
Semi.o: Semi.cpp Semi.h Symbols.h Shell.h
	$(CC) Semi.cpp $(CFLAGS) -c

Pound.o: Pound.cpp Pound.h Shell.h
	$(CC) Pound.cpp $(CFLAGS) -c

clean:
	rm -r bin