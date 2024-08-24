ifneq (,)
requires GNU make.
endif

ifeq ($(origin CC),default)
CC := gcc
endif

CFLAGS = -DLIBGO_COMPILE -fPIC 
LDFLAGS = -shared

includes = -Iinclude
precompile = -include types.h

bin = libgo.so
src = $(wildcard src/*.c)
obj = $(src:.c=.o)

.PHONY: all
all: $(bin)

$(bin): $(obj)
	$(CC) $(LDFLAGS) -o $@ $(obj)
%.o: %.c
	$(CC) $(CFLAGS) $(includes) $(precompile) -c -o $@ $<

.PHONY: test
test: test_main

test_main: test/test.c
	LD_LIBRARY_PATH=. $(CC) -L. -lgo $(includes) -o $@ $< 

.PHONY: clean
clean:
	$(RM) $(obj)
	$(RM) $(bin)
	$(RM) test_main
