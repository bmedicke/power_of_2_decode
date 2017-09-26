BIN=decode

all: main.c decode.o decode.h helpers.h helpers.o
	gcc main.c decode.o helpers.o -o $(BIN)

clean:
	rm $(BIN)

run:
	./$(BIN)

format:
	astyle *.c
