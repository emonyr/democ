#Makefile designed Johnny Yang

#environment variant
USER_HEADER	:= ./include
TARGET	:= myserver
COMPONENTS	+= main.o
COMPONENTS	+= connection.o
COMPONENTS	+= protocal.o

CROSS_COMPILE	:= 
CC	:= $(CROSS_COMPILE)gcc
LD	:= $(CROSS_COMPILE)ld
CFLAGS	:= -Wall -I$(USER_HEADER)
LDLAGS	:= 

#compile commands
All: $(TARGET)

$(TARGET): $(COMPONENTS)
	$(LD) $(LDLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o myserver