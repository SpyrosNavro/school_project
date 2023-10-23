#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#pragma once

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

int** import_data(const char *file_name, int vrows);
int compute_distance (Node a, Node b, int dim);
Graph createGraph(int nedges, const char *file_name, int row, int column);
int deleteGraph(Graph graph);