# Define variables
CC = gcc
CFLAGS = -Wall -O2
TARGET = my_program

# Define the source files and object files
SRCS = FirmwareCommunication.c GeneralFunctions.c ModeRouting.c Radio.c Startup.c StateMachine.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)


