#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#pragma once
#define THREAD_NUM 4

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

struct graph {
    Node* nodes;
    int dim, nnodes, neighbors;
};

// structure of nodes 
struct node {
    int id;    // id of point 
    int checked;
    int same;
    int nreverse;
    Edge* edges;
    Edge* reverse;
    //bool* true_rev;
    int* coord;  // coordinates of n-dimentional point
    int norm;
};

// structure of edge
struct edge {
    int src, dest;
    float distance;
    bool is;
    bool rev_is;
};

typedef struct init {
    void (*taskFunction)(Graph, int, int, int**);
    Graph graph;
    int id, column;
    int** data;
} init;

void executeTask (init* task);
void submitTask (init task);
void* startThread();

int** import_data(const char *file_name, int vrows);
float** import_Binarydata(const char *file_name);

float euclideanDistance(Node a, Node b, int dim);
float euclideanDistanceTest (Node a, Node b, int dim);
float manhattanDistance (Node a, Node b, int dim);
void initialiseData(Graph graph, int id, int column, int** data);
Graph createGraph(int nedges, const char *file_name, int row, int column);
Graph createGraphTest (int nedges, const char *file_name, int row, int column);
void deleteGraph(Graph graph);