ifneq (,)
requires GNU make.
endif

ifeq ($(origin CC),default)
CC := gcc
endif

dir := ../src
files := $(dir)/*.c
obj := $(files:.c=.o)

all:
	@echo $(files)
