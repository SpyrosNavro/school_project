OBJS1 = graph.o pqueue.o nndescent.o nnd_functions.o # tests.o
OBJS2 = pqueue.o testPQ.o #nndescent.o
OBJS3 = graph.o testGraph.o random_projection.o pqueue.o
OBJ = pqueue.o testPQ.o graph.o testGraph.o random_projection.o
OBJS = graph.o pqueue.o nndescent.o testPQ.o testGraph.o nnd_functions.o random_projection.o
OUT = nndescent testpq testgraph
OUT1 = nndescent
OUT2 = testpq
OUT3 = testgraph
CC = gcc
FLAGS = -g -c -Wall -lm -Wextra -pthread
FILES = ./data_structures/
FILES2 = ./nnd_files/
TESTS = ./tests/

nndescent: $(OBJS1)
	$(CC) -g -Wall -o $(OUT1) $(OBJS1) -lm

testpq: $(OBJS2)
	$(CC) -g -Wall -o $(OUT2) $(OBJS2) -lm

testgraph: $(OBJS3)
	$(CC) -g -Wall -o $(OUT3) $(OBJS3) -lm

graph.o : $(FILES)graph.c 
	$(CC) $(FLAGS) $(FILES)graph.c 

pqueue.o : $(FILES)pqueue.c
	$(CC) $(FLAGS) $(FILES)pqueue.c

random_projection.o : $(FILES)random_projection.c
	$(CC) $(FLAGS) $(FILES)random_projection.c

nndescent.o : $(FILES2)nndescent.c 
	$(CC) $(FLAGS) $(FILES2)nndescent.c

testPQ.o : $(TESTS)testPQ.c  
	$(CC) $(FLAGS) $(TESTS)testPQ.c 

testGraph.o : $(TESTS)testGraph.c  
	$(CC) $(FLAGS) $(TESTS)testGraph.c 

nnd_functions.o: $(FILES2)nnd_functions.c 
	$(CC) $(FLAGS) $(FILES2)nnd_functions.c 

run : $(OBJ)
	$(CC) -g -Wall -o $(OUT2) $(OBJS2) -lm
	./testpq
	$(CC) -g -Wall -o $(OUT3) $(OBJS3) -lm
	./testgraph

valgrind: $(OUT)
#rm -f /tmp/*.out 
	valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean :
	rm -f /tmp/*.out 
	rm -f $(OBJS) $(OUT)
	clear