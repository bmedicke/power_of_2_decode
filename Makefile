BIN=decode
IN_FILE=in
OUT_FILE=out
STAT_FILE=stat
SYMLINK_TARGET=/usr/local/bin

COMPILER=clang

# enable all warnings:
FLAGS=-Weverything

# set dialect:
FLAGS+= -std=c99

# forgo optimisations for valgrind and debugging:
FLAGS+= -O0 -g

all: main.c decode.h decode.o helpers.h helpers.o
	$(COMPILER) $(FLAGS) main.c decode.o helpers.o -o $(BIN)

clean:
	rm $(BIN) out stat *.o
	rm -rf html
	rm -rf $(decode).dSYM

run:
	./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

verbose:
	./$(BIN) -v -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

help:
	./$(BIN) -h

format:
	astyle -A2 *.{c,h} && git diff

link:
	/bin/ln -ns $(CURDIR)/$(BIN) $(SYMLINK_TARGET)

watch:
	ls *.{c,h} | entr sh -c "clear;make && hr ─ && make run"

doc:
	ls *.{h,c,md} Doxyfile | entr doxygen

check:
	valgrind --track-origins=yes ./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE) > report 2>&1
