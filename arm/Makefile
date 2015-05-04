#Makefile designed for major project

ENV			?= SD

TARGET			:= start.bin
BUILD			:= start
COMPONENT		+= main.o
COMPONENT		+= start.o

SDTOOL			:= ./mkv210_image
LINKER_SCRIPT	:= -Tmap.lds

CROSS_COMPILE		:= arm-linux-
CC			:= $(CROSS_COMPILE)gcc
LD			:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy

USER_HEADER		:= ./include
CFLAGS			:= -Wall -I$(USER_HEADER)
LDFLAGS			?= -Ttext=0x0
ifeq ($(ENV),RAM)
LDFLAGS			:= -Ttext=0x20000000
endif




#compile command

All : $(TARGET)
$(TARGET) : $(BUILD)
ifeq ($(ENV),RAM)
	$(OBJCOPY) -O binary $^ $@
else
	$(OBJCOPY) -O binary $^ $@.TMP
	$(SDTOOL) $@.TMP $@
endif


$(BUILD) : $(COMPONENT)
	$(LD) $(LINKER_SCRIPT) $(LDFLAGS) -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^
%.o : %.S
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o $(TARGET) $(BUILD) $(COMPONENT) *.TMP





