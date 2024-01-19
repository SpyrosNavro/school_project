#include "tests.h"
#include "../header_files/acutest.h"


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

    result = euclideanDistanceTest(a, b, dim);

    free(a->coord);
    free(b->coord);
    free(a);
    free(b);
    TEST_ASSERT(fabs(result - 9.055386) < 0.1);
}


void test_import(void) 
{
    int row = 9759;
    int** array = import_data("datasets/5k.txt", row);

    TEST_ASSERT(array != NULL);
    if(array !=NULL )
     {
        // delete vector 
        for (int i=0; i< 9759; i++)
         {
            free(array[i]);
        }
        free(array);
     }
     else{
        printf("Failed to create vector ");
     }
}


void test_importBinarydata(void) 
{
    const char *filename = "datasets/secondfile.bin";
    
    float** vector = import_Binarydata(filename); 
    TEST_ASSERT(vector != NULL);
    
    if(vector !=NULL )
    {
        // delete vector 
        for (int i=0; i< 50; i++)
         {
            free(vector[i]);
        }
        free(vector);
    }
    else
    {
        printf("Failed to create vector ");
    }
 
}


void test_create(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;

    Graph graph = createGraphTest(nedges, "datasets/5k.txt", row, column);
    TEST_ASSERT(graph != NULL);

    deleteGraph(graph);
}



void test_delete(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;

    Graph graph = createGraphTest(nedges, "datasets/5k.txt", row, column);
    deleteGraph(graph);
    TEST_ASSERT(graph != NULL);
}

TEST_LIST = {
    { "import_data", test_import },
    { "test_importBinarydata", test_importBinarydata },
    { "createGraph", test_create },
    { "deleteGraph", test_delete },
    { "euclideanDistance", test_compute},
    { NULL, NULL }
};