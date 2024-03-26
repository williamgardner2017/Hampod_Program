CC = gcc
CFLAGS = -Wall -Werror -Iinclude -g -lm -DTESTING -DOUTPUTLEVEL2 -DOUTPUTLEVEL1
LDFLAGS = -L. -lmylibrary lhamlib -lwiringPi -lpthread
TARGET = myprogram
LIBRARY = libmylibrary.so
SRCS = Modes/TestDMode.c UnitTesting/UnitTesting.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(LIBRARY): Modes/mylibrary.o
    $(CC) $(CFLAGS) -shared -o $(LIBRARY) Modes/mylibrary.o

$(TARGET): $(LIBRARY) UnitTesting/UnitTesting.o
    $(CC) $(CFLAGS) -o $(TARGET) UnitTesting/UnitTesting.o $(LDFLAGS)

src/%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

install: $(LIBRARY)
    cp $(LIBRARY) /usr/local/lib
    ldconfig

clean:
    rm -f src/*.o $(LIBRARY) $(TARGET)
	@rm -f /s *.o   # Remove object files
	# @rm -f /s ../Firmware/*.o   # Remove object files
	@rm -f *.exe  # Remove the executable (replace 'my_program' with the actual name)
	@rm -f *.elf
	@rm -f *.wav
