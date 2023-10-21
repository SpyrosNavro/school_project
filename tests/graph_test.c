#include "graph.h"  
#include "acutest.h"

void test_import(const char *file_name, int row, int column) 
{
    int** array = import_data(file_name, row, column);

    TEST_ASSERT(array != NULL);
}

void test_create(void)
{
    return 0;
}

TEST_GRAPH = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { NULL, NULL }
};