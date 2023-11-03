#include "acutest.h"

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct graph {
    Node* nodes;
    int dim, nnodes, neighbors;
    int* checked;
};

// structure of nodes 
struct node {
    int id;    // id of point 
    int nreverse;
    int* coord;  // coordinates of n-dimentional point
    Edge* edges;
    Edge* reverse;
};

// structure of edge
struct edge {
    int src, dest;
    float distance;
};





void test_compute (void)
{
    Node a;
    Node b;
    int dim = 2;
    float result;
    
    // allocate nodes
    a = malloc(sizeof(*a));
    b = malloc(sizeof(*b));

    // allocate array of coordinates
    a->coord = (int*)malloc(dim * sizeof( *(a->coord) ));
    b->coord = (int*)malloc(dim * sizeof( *(b->coord) ));

    // random coordinates
    a->coord[0] = 3;
    a->coord[1] = 7;

    b->coord[0] = 12;
    b->coord[1] = 8;

    result = compute_distance(a, b, dim);

    // distance of points a and b is about 9.05
    TEST_ASSERT(result == 9.05);
}





void test_import(void) 
{
    int row = 9759;
    int** array = import_data("5k.txt", row);

    TEST_ASSERT(array != NULL);
}





void test_create(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;

    Graph graph = createGraph(nedges, "5k.txt", row, column);
    TEST_ASSERT(graph != NULL);
    deleteGraph(graph);
}






void test_delete(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;
    int result;

    Graph graph = createGraph(nedges, "5k.txt", row, column);
    TEST_ASSERT(graph != NULL);
    result = deleteGraph(graph);
    TEST_ASSERT(graph == 1);
}

//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//

TEST_GRAPH = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { "deleteGraph", test_delete },
    { "compute_distance", test_compute},
    { NULL, NULL }
};