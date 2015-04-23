#Makefile designed for major project

ENV				?= SD

TARGET			:= start.bin
COMPONENT		+= start.o

CROSS_COMPILE	:= arm-linux-
CC				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy

USER_HEADER		:= ./include
CFLAGS			:= -Wall -I$(USER_HEADER)
LDFLAGS			?= -Ttext=0x0
ifeq ($(ENV),RAM)
LDFLAGS			:= -Ttext=0x20000000
endif







#compile command

All : $(TARGET)
$(TARGET) : $(COMPONENT)
	$(LD) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $@ $^
%.o : %.S
	$(CC) $(CFLAGS) -c $@ $^

clean:
	rm -f *.o $(TARGET) $(COMPONENT)





