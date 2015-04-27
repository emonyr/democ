All : build
build : main.o list.o
	gcc -I. -o build main.o list.o

%.o : %.c
	gcc -I. -c $^

clean :
	rm -f *.o build

