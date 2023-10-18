firmware.elf: firmware.o
	cc firmware.o -o firmware.elf -lpthread
firmware.o: firmware.c
	cc $(CFLAGS) -c firmware.c -o firmware.o -lpthread
firmware.c:
	@echo "Missing firmware.c file. Repull the git repo"

debug:
	@echo "Building Debug version"
	cc -DDEBUG -g -c firmware.c -o firmware.o -lpthread
	cc firmware.o -o firmware.elf -lpthread

clean:
	@rm *.o
	@rm *.elf
