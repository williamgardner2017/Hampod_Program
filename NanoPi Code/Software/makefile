CC = gcc
CFLAGS = -Wall -pthread -g
TARGETTEST = RunUnitTests
TARGETNORMAL = Hampod

SRCNORMAL := $(wildcard *.c) $(wildcard Modes/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
OBJSNORMAL := $(SRCNORMAL:.c=.o)

SRCTESTS := $(filter-out Startup.c, $(wildcard *.c)) $(wildcard Modes/*.c) $(wildcard UnitTesting/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
OBJSTESTS := $(SRCTESTS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

tests: $(OBJSTESTS)
	$(CC) $(CFLAGS) -o $@ $^ 

hampod: $(OBJSNORMAL)
	$(CC) $(CFLAGS) -o $@ $^



cleanWindows:
	del /s *.o
	del *.exe

clean:
 	rm -f /s *.o   # Remove object files
    rm -f *.exe  # Remove the executable (replace 'my_program' with the actual name)