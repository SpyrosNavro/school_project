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

    result = euclideanDistance(a, b, dim);

    free(a);
    free(b);
    // distance of points a and b is about 9.05
    int yes=1;
    if(result==9.055386){
        yes=0;
    }
    
    TEST_ASSERT(yes== 1);

}


void test_import(void) 
{
    int row = 9759;
    int** array = import_data("test_files/5k.txt", row);

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
   
    const char *filename = "test_files/secondfile.bin";
    
    float** vector = import_Binarydata(filename); 
    TEST_ASSERT(vector != NULL);
    

    // for (int i =0; i< 3; i++){
    //     printf("row %d:\n", i);

    //     for(int j=0; j < 3; j++){
    //         printf("%d \n", vector[i][j] );

    //     }
    // }
    
     if(vector !=NULL )
     {
        // delete vector 
        for (int i=0; i< 50; i++)
         {
            free(vector[i]);
        }
         free(vector);
     }
     else{
         printf("Failed to create vector ");
     }
 
}


void test_create(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;

    Graph graph = createGraph(nedges, "test_files/5k.txt", row, column);
    TEST_ASSERT(graph != NULL);
    
    for (int i = 0; i < graph->nnodes - 1; i++)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            //free(graph->nodes[i]->edges[j]);
            //free(graph->nodes[i]->reverse);
        }
        free(graph->nodes[i]);
    }

    free(graph);
}



void test_delete(void)
{
    int nedges = 2;
    int row = 9759;
    int column = 3;

    Graph graph = createGraph(nedges, "test_files/5k.txt", row, column);
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