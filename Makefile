ifneq (,)
requires GNU make.
endif

ifeq ($(origin CC),default)
CC := gcc
endif

ifndef CFLAGS
CFLAGS = -O2
endif

CFLAGS += -fPIC
CFLAGS += -DLIBGO_COMPILE

ifndef LDFLAGS
LDFLAGS = 
endif

LDFLAGS += -shared

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

test_main: $(bin) test/test.c
	LD_LIBRARY_PATH=. $(CC) -L. -lgo $(includes) -o $@ $(filter-out $<,$^)

.PHONY: clean
clean:
	$(RM) $(obj)
	$(RM) $(bin)
	$(RM) test_main
