#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#pragma once

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

int** import_data(const char *file_name, int row, int column);
Graph createGraph(int nedges, const char *file_name, int row, int column);
void deleteGraph(Graph graph);