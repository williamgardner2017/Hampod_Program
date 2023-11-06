CC = gcc
CFLAGS = -Wall -g
TARGETTEST = RunUnitTests
TARGETNORMAL = Hampod

SRCNORMAL := $(wildcard *.c) $(wildcard Modes/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
OBJSNORMAL := $(SRCNORMAL:.c=.o)

SRCTESTS := $(filter-out Startup.c, $(wildcard *.c)) $(wildcard Modes/*.c) $(wildcard UnitTesting/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
OBJSTESTS := $(SRCTESTS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -lpthread

.PHONY: clean

tests: $(OBJSTESTS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

hampod: $(OBJSNORMAL)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread


hampodtwo: software.o

software.o: software.c
	gcc -g -Wall -c Startup.c -o software.o -lwiringPi -lpthread
software.c:
	@echo "Missing firmware.c file. Repull the git repo"

cleanWindows:
	del /s *.o
	del *.exe

clean:
	@rm -f /s *.o   # Remove object files
	@rm -f /s ../Firmware/*.o   # Remove object files
	@rm -f *.exe  # Remove the executable (replace 'my_program' with the actual name)