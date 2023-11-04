OBJS = graph.o pqueue.o nndescent.o test.o
OUT = main
CC = gcc
FLAGS = -g -c -Wall -lm

all : $(OBJS)
	rm -f /tmp/*.out 
	$(CC) -g -Wall -o $(OUT) $(OBJS) -lm

graph.o : ./data_structures/graph.c 
	$(CC) $(FLAGS) ./data_structures/graph.c 

pqueue.o : ./data_structures/pqueue.c
	$(CC) $(FLAGS) ./data_structures/pqueue.c

nndescent.o : ./nndescent.c 
	$(CC) $(FLAGS) ./nndescent.c

test.o : ./tests/test.c  
	$(CC) $(FLAGS) ./tests/test.c 

valgrind: $(OUT)
	rm -f /tmp/*.out 
	valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean :
	rm -f /tmp/*.out 
	rm -f $(OBJS) $(OUT)