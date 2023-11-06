#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#pragma once

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

struct graph {
    Node* nodes;
    int dim, nnodes, neighbors;
    int* checked;
};

// structure of nodes 
struct node {
    int id;    // id of point 
    int nreverse;
    Edge* edges;
    Edge* reverse;
    int* coord;  // coordinates of n-dimentional point
};

// structure of edge
struct edge {
    int src, dest;
    float distance;
};

int** import_data(const char *file_name, int vrows);
float** import_Binarydata(const char *file_name);

float compute_distance(Node a, Node b, int dim);
Graph createGraph(int nedges, const char *file_name, int row, int column);
void deleteGraph(Graph graph);