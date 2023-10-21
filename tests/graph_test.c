#include "graph.h"  
#include "acutest.h"

#define row 2
#define column 2
#define file_name "file.txt"

void test_import(void) 
{
    int** array = import_data(file_name, row, column);

    TEST_ASSERT(array != NULL);
}

void test_create(void)
{
    int nedges = 2;
    Graph graph = createGraph(nedges, file_name, row, column);
    TEST_ASSERT(graph != NULL);
    deleteGraph(graph);
}

TEST_GRAPH = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { NULL, NULL }
};