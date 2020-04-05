CC:= gcc
CCFLAGS:= -g -Wall -Werror

TARGETS:= jia
SRC:= jia.c

.PHONY: all

all:
	$(CC) $(CCFLAGS) -o $(TARGETS) $(SRC)
