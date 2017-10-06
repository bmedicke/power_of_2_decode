BIN=decode
IN_FILE=in
OUT_FILE=out
STAT_FILE=stat

COMPILER=clang
# COMPILER=gcc

FLAGS=-Weverything
# FLAGS=-Wall

all: main.c decode.h decode.o helpers.h helpers.o
	$(COMPILER) $(FLAGS) main.c decode.o helpers.o -o $(BIN)

clean:
	rm $(BIN) out stat *.o
	rm -rf html

run:
	./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

verbose:
	./$(BIN) -v -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

help:
	./$(BIN) -h

format:
	astyle -A2 *.{c,h} && git diff

link:
	/bin/ln -fns $(CURDIR)/$(BIN) /usr/local/bin

watch:
	ls *.{c,h} | entr sh -c "clear;make && hr ─ && make run"

doc:
	ls *.{h,c,md} Doxyfile | entr doxygen
