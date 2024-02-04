# CC = gcc
CFLAGS = -Wall -g -lm
LDFLAGS = -lhamlib
Level0: Software.elf
Level1: Software1.elf
Level2: Software2.elf

Software.elf: Startup.o
	cc $(CFLAGS) -o Software.elf Startup.o -lpthread $(LDFLAGS)
Software1.elf: Startup1.o
	cc $(CFLAGS) -o Software1.elf Startup1.o -lpthread $(LDFLAGS)
Software2.elf: Startup2.o
	cc $(CFLAGS) -o Software2.elf Startup2.o -lpthread $(LDFLAGS)


Startup.o: Startup.c
	cc $(CFLAGS) -c Startup.c -o Startup.o -lpthread $(LDFLAGS)
Startup1.o: Startup.c
	cc $(CFLAGS) -c -DOUTPUTLEVEL1 Startup.c -o Startup1.o -lpthread $(LDFLAGS)
Startup2.o: Startup.c
	cc $(CFLAGS) -c -DOUTPUTLEVEL2 -DOUTPUTLEVEL1 Startup.c -o Startup2.o -lpthread $(LDFLAGS)
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

testing0: UnitTesting0.elf
testing1: UnitTesting1.elf
testing2: UnitTesting2.elf
UnitTesting0.elf: UnitTesting0.o
	cc $(CFLAGS) -o UnitTesting0.elf UnitTesting0.o -lpthread $(LDFLAGS)
UnitTesting1.elf: UnitTesting1.o
	cc $(CFLAGS) -o UnitTesting1.elf UnitTesting1.o -lpthread $(LDFLAGS)
UnitTesting2.elf: UnitTesting2.o
	cc $(CFLAGS) -o UnitTesting2.elf UnitTesting2.o -lpthread $(LDFLAGS)


UnitTesting0.o: UnitTesting.c
	cc $(CFLAGS) -DTESTING -c UnitTesting/UnitTesting.c -o UnitTesting0.o -lpthread $(LDFLAGS)
UnitTesting1.o: UnitTesting.c
	cc $(CFLAGS) -DTESTING -DOUTPUTLEVEL1 -c UnitTesting/UnitTesting.c -o UnitTesting1.o -lpthread $(LDFLAGS)
UnitTesting2.o: UnitTesting.c
	cc $(CFLAGS) -DTESTING -DOUTPUTLEVEL2 -DOUTPUTLEVEL1 -c UnitTesting/UnitTesting.c -o UnitTesting2.o -lpthread $(LDFLAGS)
UnitTesting.c:
	@echo "Missing firmware.c file. Repull the git repo"

