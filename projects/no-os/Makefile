start.bin:start.o main.o
	arm-linux-gnueabihf-ld -Ttext 0x20000000 -o start.elf start.o main.o
	arm-linux-gnueabihf-objcopy -O binary -S start.elf start.bin
	
%.o:%.S
	arm-linux-gnueabihf-gcc-4.9 -c -o $@ $^
%.o:%.c
	arm-linux-gnueabihf-gcc-4.9 -c -o $@ $^

clean:
	rm -f *.o *.elf *.bin
