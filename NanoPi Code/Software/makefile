CC = gcc
CFLAGS = -g
TARGET = RunUnitTests

SRCS := $(wildcard *.c) $(wildcard Modes/*.c) $(wildcard UnitTesting/*.c)
OBJS := $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	del /s *.o
	del *.exe