#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#pragma once


struct checking{   // the nodes that are checked, and have been put inside the queue 
    Node node; 
    float distance; 
};

struct PQueue{
    struct checking* array;
    int capacity; 
    int size;
};

struct PQueue* createPQueue(int capacity);
void insertPQueue(struct PQueue* pqueue, Node node, float distance);
void destroyPQueue(struct PQueue* pqueue);
int searchPQueue(struct PQueue* pqueue, Node node);

void swap(struct checking* a, struct checking* b);
void heapify(struct PQueue* pqueue, int root);
struct checking extractMin(struct PQueue* pqueue);
int isEmpty(struct PQueue* pqueue);