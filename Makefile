OBJS1 = graph.o pqueue.o nndescent.o # tests.o
OBJS2 = graph.o pqueue.o tests.o #nndescent.o
OBJS = graph.o pqueue.o nndescent.o tests.o
OUT1 = nndescent
OUT2 = test
OUT = nndescent test
CC = gcc
FLAGS = -g -c -Wall -lm -Wextra
FILES = ./data_structures/
TESTS = ./tests/

nndescent: $(OBJS1)
	$(CC) -g -Wall -o $(OUT1) $(OBJS1) -lm

tests: $(OBJS2)
	$(CC) -g -Wall -o $(OUT2) $(OBJS2) -lm

graph.o : $(FILES)graph.c 
	$(CC) $(FLAGS) $(FILES)graph.c 

pqueue.o : $(FILES)pqueue.c
	$(CC) $(FLAGS) $(FILES)pqueue.c

nndescent.o : ./nndescent.c 
	$(CC) $(FLAGS) ./nndescent.c

tests.o : $(TESTS)tests.c  
	$(CC) $(FLAGS) $(TESTS)tests.c 

run : $(OBJS2)
	$(CC) -g -Wall -o $(OUT) $(OBJS2) -lm
	./main 

valgrind: $(OUT)
	rm -f /tmp/*.out 
	valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean :
	rm -f /tmp/*.out 
	rm -f $(OBJS) $(OUT)
	clear