CC ?= gcc
cflags = -DLIBGO_COMPILE -fPIC 
ldflags = -shared
include = -Isrc

src = src/main.c
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

#-Wl,-rpath,.
test_main: test/test.c
	LD_LIBRARY_PATH=. $(CC) -L. -lgo $(include) -o $@ $< 

%.o: %.c
	$(CC) $(cflags) $(include) -c -o $@ $<
