firmware.elf: firmware.o
	cc firmware.o -o firmware.elf
firmware.o: firmware.c
	cc $(CFLAGS) -c firmware.c -o firmware.o
firmware.c:
	@echo "Missing firmware.c file. Repull the git repo"

debug:
	@echo "Building Debug version"
	cc -DDEBUG -g -c firmware.c -o firmware.o
	cc firmware.o -o firmware.elf

clean:
	@rm *.o
	@rm *.elf
