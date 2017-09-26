BIN=decode

all: main.c decode.o decode.h helpers.h helpers.o
	gcc main.c decode.o helpers.o -o $(BIN)

clean:
	rm $(BIN)

run:
	./$(BIN) -i in -o out -s stat

verbose:
	./$(BIN) -i in -o out -s stat -v

help:
	./$(BIN) -h

format:
	astyle *.c
