CC=g++

CFLAGS=-Wall -Werror -ansi -pedantic#-c not included here because it can't be used to run object files, a

all: main.o And.o Bar.o Commands.o Semi.o
	mkdir -p bin/
	$(CC) main.o And.o Bar.o Commands.o Semi.o -o bin/rshell

rshell: main.o And.o Bar.o Commands.o Semi.o
	mkdir -p bin/
	$(CC) main.o And.o Bar.o Commands.o Semi.o -o bin/rshell

main.o: main.cpp Commands.h And.h Bar.h Semi.h Shell.h
	$(CC) ./src/main.cpp $(CFLAGS) -c

And.o: And.cpp And.h Symbols.h Shell.h
	$(CC) ./src/And.cpp $(CFLAGS) -c

Bar.o: Bar.cpp Bar.h Symbols.h Shell.h
	$(CC) ./src/Bar.cpp $(CFLAGS) -c
    
Commands.o: Commands.cpp Commands.h Shell.h
	$(CC) ./src/Commands.cpp $(CFLAGS) -c
	
Semi.o: Semi.cpp Semi.h Symbols.h Shell.h
	$(CC) ./src/Semi.cpp $(CFLAGS) -c

clean:
	rm -rf bin