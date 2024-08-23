CC ?= gcc
cflags = -DLIBGO_COMPILE -fPIC 
ldflags = -shared
include = -Iinclude
precompile = -include types.h

src = src/node.c src/prop.c src/parse.c src/board.c src/game.c
obj = $(src:.c=.o)
bin = libgo.so

.PHONY: all clean test

all: $(bin)

clean:
	$(RM) $(obj)
	$(RM) $(bin)

test: test_main

$(bin): $(obj)
	$(CC) $(ldflags) -o $@ $(obj)

test_main: test/test.c
	LD_LIBRARY_PATH=. $(CC) -L. -lgo $(include) -o $@ $< 

%.o: %.c
	$(CC) $(cflags) $(include) $(precompile) -c -o $@ $<
