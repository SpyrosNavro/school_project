#include "acutest.h"

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"



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

TEST_GRAPH = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { "deleteGraph", test_delete },
    { NULL, NULL }
};