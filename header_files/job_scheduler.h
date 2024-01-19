#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "graph.h"

// #define THREAD_NUM 4

// typedef struct init {
//     void (*taskFunction)(Graph, int, /*int,*/ int, int**);
//     Graph graph;
//     int id, row, column;
//     int** data;
// } init;

// void executeTask (init* task);
// void submitTask (init task);
// void* startThread();