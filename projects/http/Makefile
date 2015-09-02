#Makefile designed by Johnny Yang

#environment variant
TARGET	:= jyserver
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
	$(CC) $(CFLAGS) -D__DEBUG__ -o $@ $^ -lpthread

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(COMPONENTS)