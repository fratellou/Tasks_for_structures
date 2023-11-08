CFLAGS=-Wall -Wextra -Werror

all: Quest_1 Quest_2 Quest_3 Quest_4 Quest_5 Quest_6

Quest_1: quest_1.o stack.o
	gcc $(CFLAGS) main.o stack.o -o quest_1

Quest_2: quest_2.o set.o
	gcc $(CFLAGS) main.o set.o -o quest_2

Quest_3: quest_3.o array.o
	gcc $(CFLAGS) main.o array.o -o quest_3

Quest_4: quest_4.o tree.o
	gcc $(CFLAGS) main.o tree.o -o quest_4

Quest_5: quest_5.o queue.o
	gcc $(CFLAGS) main.o queue.o -o quest_5

Quest_6: quest_6.o hash.o
	gcc $(CFLAGS) main.o hash.o -o quest_6

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

quest_1.o: stack.c stack.h main.c main.h
	gcc $(CFLAGS) -DQUEST1 main.c -c 

quest_2.o: set.c set.h main.c main.h
	gcc $(CFLAGS) -DQUEST2 main.c -c

quest_3.o: array.c array.h main.c main.h
	gcc $(CFLAGS) -DQUEST3 main.c -c

quest_4.o: tree.c tree.h main.c main.h
	gcc $(CFLAGS) -DQUEST4 main.c -c

quest_5.o: queue.c queue.h main.c main.h
	gcc $(CFLAGS) -DQUEST5 main.c -c

quest_6.o: hash.c hash.h main.c main.h
	gcc $(CFLAGS) -DQUEST6 main.c -c

clean: 
	rm -rf *.o quest_1 quest_2 quest_3 quest_4 quest_5 quest_6

rebuild: clean all