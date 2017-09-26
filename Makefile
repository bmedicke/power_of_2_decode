BIN=decode

all:
	gcc *.c -o $(BIN)

clean:
	rm $(BIN)

run:
	./$(BIN)

format:
	astyle *.c
