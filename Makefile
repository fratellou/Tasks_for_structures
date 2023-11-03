CFLAGS=-Wall -Wextra -Werror

all:build

build: database.o hash.o stack.o array.o set.o tree.o queue.o hash.o double_set.o 
	gcc $(CFLAGS) database.o hash.o array.o tree.o stack.o set.o queue.o double_set.o -o dbms

database.o: macro.h hash.h hash.c queue.c queue.h set.c set.h stack.h stack.c database.c
	gcc $(CFLAGS) -c database.c

hash.o: macro.h hash.h hash.c
	gcc $(CFLAGS) -c hash.c

stack.o: macro.h stack.h stack.c
	gcc $(CFLAGS) -c stack.c

set.o: macro.h set.h set.c
	gcc $(CFLAGS) -c set.c

double_set.o: macro.h double_set.h double_set.c
	gcc $(CFLAGS) -c double_set.c

queue.o: macro.h queue.h queue.c 
	gcc $(CFLAGS) -c queue.c

array.o: macro.h array.h array.c 
	gcc $(CFLAGS) -c array.c

three.o: macro.h tree.h tree.c 
	gcc $(CFLAGS) -c tree.c

clean: 
	rm -rf *.o dbms

rebuild:clean all