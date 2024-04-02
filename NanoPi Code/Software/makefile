

# Makefile

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -Wall -g -lm -DTESTING -DOUTPUTLEVEL1
LDFLAGS := -lpthread -lhamlib -lwiringPi
# Files
HEADER := Modes/TestDMode.h
LIB_SRC := Modes/TestDMode.h
EXEC_SRC := UnitTesting/UnitTesting.c

# Shared library name
LIB_NAME := libyourlibrary.so

# Executable name
EXEC_NAME := testing

# Targets
all: $(EXEC_NAME)

# Build shared library
$(LIB_NAME): $(LIB_SRC) $(HEADER)
	$(CC) $(CFLAGS) -DSHAREDLIB -fPIC -shared -o $(LIB_NAME) $(LIB_SRC) $(LDFLAGS)

# Build executable
$(EXEC_NAME): $(EXEC_SRC) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(EXEC_SRC) -I. -L. -l:$(LIB_NAME) -ldl $(LDFLAGS) -Wl,-rpath,'$$ORIGIN'

# Clean
clean:
	rm -f $(LIB_NAME) $(EXEC_NAME)
	rm -f src/*.o $(LIBRARY) $(TARGET)
	@rm -f /s *.o   # Remove object files
	# @rm -f /s ../Firmware/*.o   # Remove object files
	@rm -f *.exe  # Remove the executable (replace 'my_program' with the actual name)
	@rm -f *.elf
	@rm -f *.wav

# Phony targets
.PHONY: all clean
