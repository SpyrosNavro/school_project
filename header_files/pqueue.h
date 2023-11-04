#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#pragma once

struct PQueue* createPQueue(int capacity);
void insertPQueue(struct PQueue* pqueue, Node node, float distance);
void destroyPQueue(struct PQueue* pqueue);


void swap(struct checking* a, struct checking* b);
void heapify(struct PQueue* pqueue, int root);
struct checking extractMin(struct PQueue* pqueue);
int isEmpty(struct PQueue* pqueue);