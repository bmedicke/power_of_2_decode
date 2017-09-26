BIN=decode

all: main.c decode.o decode.h
	gcc main.c decode.o -o $(BIN)

clean:
	rm $(BIN)

run:
	./$(BIN)

format:
	astyle *.c
