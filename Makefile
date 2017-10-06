BIN=decode
IN_FILE=in
OUT_FILE=out
STAT_FILE=stat

COMPILER=clang
FLAGS=-Weverything

all: main.c decode.o decode.h helpers.h helpers.o
	$(COMPILER) $(FLAGS) main.c decode.o helpers.o -o $(BIN)

clean:
	rm $(BIN) out stat *.o

run:
	./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

verbose:
	./$(BIN) -v -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

help:
	./$(BIN) -h

format:
	astyle -A2 *.c *.h

link:
	/bin/ln -fns $(CURDIR)/$(BIN) /usr/local/bin
