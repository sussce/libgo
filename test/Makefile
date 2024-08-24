ifneq (,)
requires GNU make.
endif

ifeq ($(origin CC),default)
CC := gcc
endif

bin = libgo.so

src = libgo.c

all:  test_main

test_main: $(bin) $(src)
	@echo $(<F)
