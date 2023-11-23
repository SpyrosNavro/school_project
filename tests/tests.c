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

    result = compute_distance(a, b, dim);

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
    deleteGraph(graph);
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


//-------------------------------------------------------//
//---------------------PRIORITY QUEUE--------------------//
//-------------------------------------------------------//


void test_createPQueue(void)
{
    struct PQueue* pqueue = createPQueue(7);
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);

    destroyPQueue(pqueue);
}



void test_insertPQueue(void)
{
    struct PQueue* pqueue = createPQueue(10);
    TEST_ASSERT(pqueue->capacity==10);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    TEST_ASSERT(mynode !=NULL);
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    TEST_ASSERT(mynode2 !=NULL);
    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    TEST_ASSERT(mynode3 !=NULL);
    mynode3->id=3;

    mynode4 = malloc(sizeof(Node));
    TEST_ASSERT(mynode4 !=NULL);
    mynode4->id=4;

    mynode5 = malloc(sizeof(Node));
    TEST_ASSERT(mynode5 !=NULL);
    mynode5->id=5;

    mynode6 = malloc(sizeof(Node));
    TEST_ASSERT(mynode6 !=NULL);
    mynode6->id=6;

    mynode7 = malloc(sizeof(Node));
    TEST_ASSERT(mynode7 !=NULL);
    mynode7->id=7;

    mynode8 = malloc(sizeof(Node));
    TEST_ASSERT(mynode8 !=NULL);
    mynode8->id=8;

    mynode9 = malloc(sizeof(Node));
    TEST_ASSERT(mynode9 !=NULL);
    mynode9->id=9;

    insertPQueue(pqueue, mynode,23);
    TEST_ASSERT(pqueue->size==1);

    insertPQueue(pqueue, mynode2,15);
    TEST_ASSERT(pqueue->size==2);
  
    insertPQueue(pqueue, mynode3,678);
    TEST_ASSERT(pqueue->size==3);

    insertPQueue(pqueue, mynode4,12);
    TEST_ASSERT(pqueue->size==4);

    insertPQueue(pqueue, mynode5,35);
    TEST_ASSERT(pqueue->size==5);

    insertPQueue(pqueue, mynode6,1278);
    TEST_ASSERT(pqueue->size==6);

    insertPQueue(pqueue, mynode7,98.56);
    TEST_ASSERT(pqueue->size==7);

    insertPQueue(pqueue, mynode8,34987.4);
    TEST_ASSERT(pqueue->size==8);


    insertPQueue(pqueue, mynode9,7899.99);
    TEST_ASSERT(pqueue->size==9);

    //printf("size of the queue is:%d\n",pqueue->size);
    free(mynode);
    free(mynode2);
    free(mynode3);
    free(mynode4);
    free(mynode5);
    free(mynode6);
    free(mynode7);
    free(mynode8);
    free(mynode9);
    
    //printf("the items of the priority queue are the following: ");

    destroyPQueue(pqueue);
}



void test_extractMin(void)
{
    struct PQueue* pqueue = createPQueue(10);
    TEST_ASSERT(pqueue->capacity==10);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    mynode = malloc(sizeof(Node));
    TEST_ASSERT(mynode !=NULL);
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    TEST_ASSERT(mynode2 !=NULL);
    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    TEST_ASSERT(mynode3 !=NULL);
    mynode3->id=3;

    mynode4 = malloc(sizeof(Node));
    TEST_ASSERT(mynode4 !=NULL);
    mynode4->id=4;

    mynode5 = malloc(sizeof(Node));
    TEST_ASSERT(mynode5 !=NULL);
    mynode5->id=5;

    mynode6 = malloc(sizeof(Node));
    TEST_ASSERT(mynode6 !=NULL);
    mynode6->id=6;

    mynode7 = malloc(sizeof(Node));
    TEST_ASSERT(mynode7 !=NULL);
    mynode7->id=7;

    mynode8 = malloc(sizeof(Node));
    TEST_ASSERT(mynode8 !=NULL);
    mynode8->id=8;

    mynode9 = malloc(sizeof(Node));
    TEST_ASSERT(mynode9 !=NULL);
    mynode9->id=9;

    insertPQueue(pqueue, mynode,289);
    TEST_ASSERT(pqueue->size==1);

    insertPQueue(pqueue, mynode2,458);
    TEST_ASSERT(pqueue->size==2);

    insertPQueue(pqueue, mynode3,98776);
    TEST_ASSERT(pqueue->size==3);

    insertPQueue(pqueue, mynode4,7657);
    TEST_ASSERT(pqueue->size==4);

    insertPQueue(pqueue, mynode5,3539);
    TEST_ASSERT(pqueue->size==5);

    insertPQueue(pqueue, mynode6,5);
    TEST_ASSERT(pqueue->size==6);

    insertPQueue(pqueue, mynode7,987);
    TEST_ASSERT(pqueue->size==7);

    insertPQueue(pqueue, mynode8,877436.8);
    TEST_ASSERT(pqueue->size==8);

    insertPQueue(pqueue, mynode9,789787);
    TEST_ASSERT(pqueue->size==9);

    struct checking min= extractMin(pqueue);
    TEST_ASSERT(min.distance==5);

    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==289);

    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==458);

    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==987);


    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==3539);
    TEST_ASSERT(min.node->id==5);
    
    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==7657);

    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==98776);

    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==789787);
    
    min= extractMin(pqueue);
    TEST_ASSERT(min.distance==877436.8125);
    TEST_ASSERT(min.node->id==8);





    while(!(isEmpty(pqueue))){
        printf("value with the smallest distance removed and has the value: %f\n", min.distance);
        
    }
    
    TEST_ASSERT(pqueue->size==0);

    free(mynode);
    free(mynode2);
    free(mynode3);
    free(mynode4);
    free(mynode5);
    free(mynode6);
    free(mynode7);
    free(mynode8);
    free(mynode9);
    
    
    destroyPQueue(pqueue);

    //return 0;
}

void test_searchPQueue(){
    struct PQueue* pqueue = createPQueue(7);
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,notexisting ;

    mynode = malloc(sizeof(Node));
    TEST_ASSERT(mynode !=NULL);
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    TEST_ASSERT(mynode2 !=NULL);
    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    TEST_ASSERT(mynode3 !=NULL);
    mynode3->id=3;

    insertPQueue(pqueue, mynode, 45);
    TEST_ASSERT(pqueue->size==1);

    insertPQueue(pqueue, mynode2,197);
    TEST_ASSERT(pqueue->size==2);
  
    insertPQueue(pqueue, mynode3,5467);
    TEST_ASSERT(pqueue->size==3);

    int i= searchPQueue(pqueue,mynode3);

    notexisting= malloc(sizeof(Node));
    notexisting->id=20;
    notexisting->coord=NULL;
    notexisting->edges=NULL;
    
    i= searchPQueue(pqueue,notexisting);
    // 1 -> does not belong to the queue
    TEST_ASSERT(i==1);
    

    free(mynode);
    free(mynode2);
    free(mynode3);
    free(notexisting);
    
    
    destroyPQueue(pqueue);



}

void test_isEmpty(){
    struct PQueue* pqueue = createPQueue(4);
    TEST_ASSERT(pqueue->capacity==4);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    TEST_ASSERT(isEmpty(pqueue)==1);

}
//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//

TEST_LIST = {
    { "import_data", test_import },
    { "test_importBinarydata", test_importBinarydata },
    { "createGraph", test_create },
    { "deleteGraph", test_delete },
    { "compute_distance", test_compute},
    { "createPQueue", test_createPQueue},
    { "insertPQueue", test_insertPQueue},
    { "extractMin", test_extractMin},
    { "searchPQueue", test_searchPQueue},
    { "isEmpty", test_isEmpty},
    { NULL, NULL }
};