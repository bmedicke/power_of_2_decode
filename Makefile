SHELL = /bin/sh
BIN = decode
IN_FILE = in
OUT_FILE = out
STAT_FILE = stat
SYMLINK_TARGET = /usr/local/bin
VALGRIND_LOG = valgrind_report
ASTYLE_CONFIG = .astylerc
OBJECTS = helpers.o decode.o
SOURCE = source
VENDOR = vendor

# tested with clang and gcc:
CC ?= clang

# use -Wall for gcc
# use -Weverything for clang
FLAGS = -Weverything # enable all warnings.

# set dialect:
FLAGS += -std=c99

# forgo optimisations for valgrind and debugging:
FLAGS += -O0 -g

# add third party libs via isystem to ignore warnings:
FLAGS += -isystem $(VENDOR)

# add my source path:
FLAGS += -I source

all: $(SOURCE)/main.c $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(SOURCE)/main.c -o $(BIN)

%.o: $(SOURCE)/%.c
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf html
	rm -rf *.dSYM
	rm $(BIN) $(OUT_FILE) $(STAT_FILE) *.o

run:
	./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

verbose:
	./$(BIN) -v -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE)

help:
	./$(BIN) -h

format:
	astyle --options=$(ASTYLE_CONFIG) $(SOURCE)/*.{c,h} && git diff

link:
	/bin/ln -ns $(CURDIR)/$(BIN) $(SYMLINK_TARGET)

watch:
	ls $(SOURCE)/*.{c,h} | entr sh -c "clear;make clean;make && hr ─ && make run | head -n4"

doc:
	ls $(SOURCE)/*.{h,c} *.md Doxyfile | entr doxygen

report: $(BIN)
	valgrind --track-origins=yes --leak-resolution=high --leak-check=full \
		--log-file="$(VALGRIND_LOG)" \
		./$(BIN) -i $(IN_FILE) -o $(OUT_FILE) -s $(STAT_FILE) 2>&1 > /dev/null
	sed "1,3d;5,6d" $(VALGRIND_LOG) | cut -d " " -f2- | sponge $(VALGRIND_LOG)
