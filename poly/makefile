CC	= cc
CFLAGS	= -std=c11 -pedantic -Wall -Werror -g -O3 -funsigned-char
OUT	= a.out
FILE	= poly

execute: compile
	./a.out > output
	diff output correct

compile: clean $(FILE).o malloc.o main.o
	$(CC) $(CFLAGS) -o $(OUT) $(FILE).o malloc.o main.o

$(FILE).o: $(FILE).c
	$(CC) -include wecc.h -c $(FILE).c $(CFLAGS)

malloc.o: malloc.c
	$(CC) -c malloc.c $(CFLAGS) 

clean:
	rm -f *.s *.o $(OUT) 

val: compile
	valgrind --leak-check=yes ./a.out

val_massif: compile
	valgrind --tool=massif --massif-out-file=massif.out ./a.out
	ms_print massif.out