#include "acutest.h"

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


/*
void test_import(void) 
{
    int** array = import_data(file_name, row, column);

    TEST_ASSERT(array != NULL);
}
*/
void test_create(void)
{
    int nedges = 2;
    Graph graph = createGraph(nedges, filename, vrows, column);
    TEST_ASSERT(graph != NULL);
    deleteGraph(graph);
}

TEST_GRAPH = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { NULL, NULL }
};

int main(){
     
    char *filename = "data_structures/5k.txt";
    int vrows=9759;
    int** vector = import_data(filename, vrows);
/*
    for (int i =0; i< 3; i++){
        printf("row %d:", i+1);
        for(int j=0; j < 3; j++) {
            printf("%d \n",vector[i][j]);
             
        }
    }
*/    
    if(vector !=NULL ){
        printf("Succesfully created the vector ");

        // delete vector 
        for (int i=0; i< vrows; i++){
            free(vector[i]);
        }
        free(vector);
    }
    else{
        printf("Failed to create vector ");
    }
    

    return 0;
}