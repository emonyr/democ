#Makefile designed by Johnny Yang

#environment variant
TARGET	:= myserver
COMPONENTS	+= main.o
COMPONENTS	+= connection.o
COMPONENTS	+= protocal.o

CROSS_COMPILE	:= 
#/usr/bin/arm-linux-gnueabi-
CC	:= $(CROSS_COMPILE)gcc
LD	:= $(CROSS_COMPILE)ld
CFLAGS	:= -Wall

#compile commands
All: $(TARGET)

$(TARGET): $(COMPONENTS)
	$(CC) $(CFLAGS) -D__DEBUG__ -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o myserver