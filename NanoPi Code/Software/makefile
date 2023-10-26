# Define variables
CC = gcc
CFLAGS = -Wall -O2
TARGET = MainSystem
TARGETT = TestingSystem
# Define the source files and object files
SRCS = Modes/ModeRouting.c FirmwareCommunication.c GeneralFunctions.c Radio.c Startup.c StateMachine.c  Modes/ConfigMode.c Modes/DummyDTMFMode.c Modes/NormalMode.c
TESTS = UnitTesting/UnitTesting.c UnitTesting/UnitTestKeyPresses.c UnitTesting/UnitTestModeRouting.c UnitTesting/UnitTestStateMachine.c
OBJS = $(SRCS:.c=.o)
OBJST = $(TESTS:.c=.o)

# Default target
main: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


test: $(TARGETT)
# Rule to build the target
$(TARGETT): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGETT): $(OBJST)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(OBJST) $(TARGETT)


