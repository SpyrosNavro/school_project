OBJS = graph.o pqueue.o nndescent.o tests.o
OUT = main
CC = gcc
FLAGS = -g -c -Wall -lm
FILES = ./data_structures/
TESTS = ./tests/

all : $(OBJS)
	rm -f /tmp/*.out 
	$(CC) -g -Wall -o -lm $(OBJS) $(OUT)

graph.o : $(FILES)graph.c 
	$(CC) $(FLAGS) $(FILES)graph.c 

pqueue.o : $(FILES)pqueue.c
	$(CC) $(FLAGS) $(FILES)pqueue.c

nndescent.o : ./nndescent.c 
	$(CC) $(FLAGS) ./nndescent.c

tests.o : $(TESTS)tests.c  
	$(CC) $(FLAGS) $(TESTS)tests.c 

valgrind: $(OUT)
	rm -f /tmp/*.out 
	valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean :
	rm -f /tmp/*.out 
	rm -f $(OBJS) $(OUT)