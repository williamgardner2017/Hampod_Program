# CC = gcc
CFLAGS = -Wall -g -lm
# TARGETTEST = RunUnitTests
# TARGETNORMAL = Hampod

# SRCNORMAL := $(wildcard *.c) $(wildcard Modes/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
# OBJSNORMAL := $(SRCNORMAL:.c=.o)

# SRCTESTS := $(filter-out Startup.c, $(wildcard *.c)) $(wildcard Modes/*.c) $(wildcard UnitTesting/*.c) ../Firmware/hampod_firm_packet.c ../Firmware/hampod_queue.c
# OBJSTESTS := $(SRCTESTS:.c=.o)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@ -lpthread

# .PHONY: clean

# tests: $(OBJSTESTS)
# 	$(CC) $(CFLAGS) -o $@ $^ -lpthread

# hampod: $(OBJSNORMAL)
# 	$(CC) $(CFLAGS) -o $@ $^ -lpthread

# firmware.elf: firmware.o
# 	cc firmware.o -o firmware.elf -lpthread

Level0: Software.elf
Level1: Software1.elf
Level2: Software2.elf

Software.elf: Startup.o
	cc $(CFLAGS) -o Software.elf Startup.o -lpthread
Software1.elf: Startup1.o
	cc $(CFLAGS) -o Software1.elf Startup1.o -lpthread
Software2.elf: Startup2.o
	cc $(CFLAGS) -o Software2.elf Startup2.o -lpthread


Startup.o: Startup.c
	cc $(CFLAGS) -c Startup.c -o Startup.o -lpthread
Startup1.o: Startup.c
	cc $(CFLAGS) -c -DOUTPUTLEVEL1 Startup.c -o Startup1.o -lpthread
Startup2.o: Startup.c
	cc $(CFLAGS) -c -DOUTPUTLEVEL2 -DOUTPUTLEVEL1 Startup.c -o Startup2.o -lpthread
Startup.c:
	@echo "Missing firmware.c file. Repull the git repo"

cleanWindows:
	del /s *.o
	del *.exe

clean:
	@rm -f /s *.o   # Remove object files
	@rm -f /s ../Firmware/*.o   # Remove object files
	@rm -f *.exe  # Remove the executable (replace 'my_program' with the actual name)
	@rm -f *.elf

testing: UnitTesting.elf
UnitTesting.elf: UnitTesting.o
	cc $(CFLAGS) -o UnitTesting.elf UnitTesting.o -lpthread
UnitTesting.o: UnitTesting.c
	cc $(CFLAGS) -DTESTING -DOUTPUTLEVEL2 -DOUTPUTLEVEL1 -c UnitTesting/UnitTesting.c -o UnitTesting.o -lpthread
UnitTesting.c:
	@echo "Missing firmware.c file. Repull the git repo"

