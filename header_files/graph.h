#pragma once

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

int** import_data(const char *file_name, int row, int column);
Graph createGraph(int nedges, const char *file_name, int row, int column);