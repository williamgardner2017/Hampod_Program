CC = gcc
CFLAGS = -Wall -Werror -Iinclude -g -lm -DTESTING -DOUTPUTLEVEL2 -DOUTPUTLEVEL1
LDFLAGS = -L. -lmylibrary -lhamlib -lwiringPi -lpthread
TARGET =  UnitTesting/UnitTesting.c
LIBRARY = libmylibrary.so
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(LIBRARY): mylibrary.o
    $(CC) $(CFLAGS) -shared -o $(LIBRARY) Modes/mylibrary.o

$(TARGET): $(LIBRARY) UnitTesting.o
    $(CC) $(CFLAGS) -o $(TARGET) UnitTesting.o $(LDFLAGS)

%.o: %.c
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


