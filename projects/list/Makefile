All : build joseph
build : main.o list.o
	gcc -I. -o build main.o list.o
joseph : joseph_circle.o list.o
	gcc -I. -o joseph joseph_circle.o list.o

%.o : %.c
	gcc -I. -c $^

clean :
	rm -f *.o build

