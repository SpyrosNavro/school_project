#include "tests.h"



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

void test_importBinarydata(void) 
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

    Graph graph = createGraph(nedges, "5k.txt", row, column);
    deleteGraph(graph);
    TEST_ASSERT(graph == NULL);
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
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    TEST_ASSERT(mynode !=NULL);

    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    TEST_ASSERT(mynode !=NULL);

    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    mynode3->id=3;

    mynode4 = malloc(sizeof(Node));
    mynode4->id=4;

    mynode5 = malloc(sizeof(Node));
    mynode5->id=5;

    mynode6 = malloc(sizeof(Node));
    mynode6->id=6;

    mynode7 = malloc(sizeof(Node));
    mynode7->id=7;

    mynode8 = malloc(sizeof(Node));
    mynode8->id=8;

    mynode9 = malloc(sizeof(Node));
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
    
    printf("the items of the priority queue are the following: ");

    destroyPQueue(pqueue);
}



void test_extractMin(void)
{
    struct PQueue* pqueue = createPQueue(10);
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    if (mynode == NULL){
        printf("could not allocate memory for node"); 
        //return 1; 
    }
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    if (mynode2 == NULL){
        printf("could not allocate memory for node"); 
        //return 1; 
    }
    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    mynode3->id=3;

    mynode4 = malloc(sizeof(Node));
    mynode4->id=4;

    mynode5 = malloc(sizeof(Node));
    mynode5->id=5;

    mynode6 = malloc(sizeof(Node));
    mynode6->id=6;

    mynode7 = malloc(sizeof(Node));
    mynode7->id=7;

    mynode8 = malloc(sizeof(Node));
    mynode8->id=8;

    mynode9 = malloc(sizeof(Node));
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

    printf("the items of the priority queue are the following: "); 
    struct checking min= extractMin(pqueue);
 

    while(!(isEmpty(pqueue))){
        min= extractMin(pqueue);
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
    struct PQueue* pqueue = createPQueue(10);
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9,notexisting ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    if (mynode == NULL){
        printf("could not allocate memory for node"); 
        //return 1; 
    }
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    if (mynode2 == NULL){
        printf("could not allocate memory for node"); 
        //return 1; 
    }
    mynode2->id=2;

    mynode3 = malloc(sizeof(Node));
    mynode3->id=3;

    mynode4 = malloc(sizeof(Node));
    mynode4->id=4;

    mynode5 = malloc(sizeof(Node));
    mynode5->id=5;

    mynode6 = malloc(sizeof(Node));
    mynode6->id=6;

    mynode7 = malloc(sizeof(Node));
    mynode7->id=7;

    mynode8 = malloc(sizeof(Node));
    mynode8->id=8;

    mynode9 = malloc(sizeof(Node));
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

    notexisting= malloc(sizeof(Node));
    notexisting->id=20;
    notexisting->coord=NULL;
    notexisting->edges=NULL;
  
    int i= searchPQueue(pqueue,notexisting);
    TEST_ASSERT(i==1);

    free(mynode);
    free(mynode2);
    free(mynode3);
    free(mynode4);
    free(mynode5);
    free(mynode6);
    free(mynode7);
    free(mynode8);
    free(mynode9);
    free(notexisting);
    
    
    destroyPQueue(pqueue);



}


//-------------------------------------------------------//
//-------------------------------------------------------//
//-------------------------------------------------------//

TEST_LIST = {
    { "import_data", test_import },
    { "createGraph", test_create },
    { "deleteGraph", test_delete },
    { "compute_distance", test_compute},
    { "createPQueue", test_createPQueue},
    { "insertPQueue", test_insertPQueue},
    { "extractMin", test_extractMin},
    { "searchPQueue", test_searchPQueue},
    { NULL, NULL }
};