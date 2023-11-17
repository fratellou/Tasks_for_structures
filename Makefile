CFLAGS=-Wall -Wextra -Werror

all: Quest_1 Quest_2 Quest_3 Quest_4 Quest_5 Quest_6

Quest_1: quest_1.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_1

Quest_2: quest_2.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_2

Quest_3: quest_3.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_3

Quest_4: quest_4.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_4

Quest_5: quest_5.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_5

Quest_6: quest_6.o stack.o hash.o set.o array.o tree.o queue.o
	gcc $(CFLAGS) main.o stack.o hash.o set.o array.o tree.o queue.o -o quest_6

hash.o: hash.h hash.c
	gcc $(CFLAGS) -c hash.c

stack.o: stack.h stack.c
	gcc $(CFLAGS) -c stack.c

set.o: set.h set.c
	gcc $(CFLAGS) -c set.c

double_set.o: double_set.h double_set.c
	gcc $(CFLAGS) -c double_set.c

queue.o: queue.h queue.c 
	gcc $(CFLAGS) -c queue.c

array.o: array.h array.c 
	gcc $(CFLAGS) -c array.c

tree.o: tree.h tree.c 
	gcc $(CFLAGS) -c tree.c

quest_1.o: main.c main.h
	gcc $(CFLAGS) -DQUEST1 main.c -c 

quest_2.o: main.c main.h
	gcc $(CFLAGS) -DQUEST2 main.c -c

quest_3.o: main.c main.h
	gcc $(CFLAGS) -DQUEST3 main.c -c

quest_4.o: main.c main.h
	gcc $(CFLAGS) -DQUEST4 main.c -c

quest_5.o: main.c main.h
	gcc $(CFLAGS) -DQUEST5 main.c -c

quest_6.o: main.c main.h
	gcc $(CFLAGS) -DQUEST6 main.c -c

clean: 
	rm -rf *.o quest_1 quest_2 quest_3 quest_4 quest_5 quest_6

rebuild: clean all