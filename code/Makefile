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

hash.o: 
	gcc $(CFLAGS) -c hash.c

stack.o:
	gcc $(CFLAGS) -c stack.c

set.o:
	gcc $(CFLAGS) -c set.c

double_set.o:
	gcc $(CFLAGS) -c double_set.c

queue.o:
	gcc $(CFLAGS) -c queue.c

array.o: 
	gcc $(CFLAGS) -c array.c

tree.o: 
	gcc $(CFLAGS) -c tree.c

quest_1.o: 
	gcc $(CFLAGS) -DQUEST1 main.c -c 

quest_2.o: 
	gcc $(CFLAGS) -DQUEST2 main.c -c

quest_3.o: 
	gcc $(CFLAGS) -DQUEST3 main.c -c

quest_4.o: 
	gcc $(CFLAGS) -DQUEST4 main.c -c

quest_5.o: 
	gcc $(CFLAGS) -DQUEST5 main.c -c

quest_6.o: 
	gcc $(CFLAGS) -DQUEST6 main.c -c

clean: 
	rm -rf *.o quest_1 quest_2 quest_3 quest_4 quest_5 quest_6

rebuild: clean all