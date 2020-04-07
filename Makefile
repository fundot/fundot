CC:= gcc
CCFLAGS:= -g -Wall -Werror

TARGETS:= jia
SRC:= jia.c  jiaio.c jialib.c str.c strv.c str_pair.c str_map.c fun.c fun_map.c debug.c

.PHONY: all

all:
	$(CC) $(CCFLAGS) -o $(TARGETS) $(SRC)
