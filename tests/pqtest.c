#include "acutest.h"

#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include "graph.h"


void test_createPQueue(){
    struct PQueue* pqueue = createPQueue(7);
    TEST_ASSERT(pqueue->capacity==7);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);

    destroyPQueue(pqueue);
}

void test_insert(){
    struct PQueue* pqueue = createPQueue(10);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    if (mynode == NULL){
        printf("could not allocate memory for node"); 
        return 1; 
    }
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    if (mynode2 == NULL){
        printf("could not allocate memory for node"); 
        return 1; 
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
    insertPQueue(pqueue, mynode2,15);
    insertPQueue(pqueue, mynode3,678);
    insertPQueue(pqueue, mynode4,12);
    insertPQueue(pqueue, mynode5,35);
    insertPQueue(pqueue, mynode6,1278);
    insertPQueue(pqueue, mynode7,98.56);
    insertPQueue(pqueue, mynode8,34987.4);
    insertPQueue(pqueue, mynode9,7899.99);


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

void test_extractMin(){
    struct PQueue* pqueue = createPQueue(10);
    Node mynode,mynode2,mynode3,mynode4,mynode5,mynode6, mynode7, mynode8,mynode9 ;

    //coord=NULL, edges=NULL;
    mynode = malloc(sizeof(Node));
    if (mynode == NULL){
        printf("could not allocate memory for node"); 
        return 1; 
    }
    mynode->id=1;
    
    mynode2 = malloc(sizeof(Node));
    if (mynode2 == NULL){
        printf("could not allocate memory for node"); 
        return 1; 
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
    insertPQueue(pqueue, mynode2,15);
    insertPQueue(pqueue, mynode3,678);
    insertPQueue(pqueue, mynode4,12);
    insertPQueue(pqueue, mynode5,35);
    insertPQueue(pqueue, mynode6,1278);
    insertPQueue(pqueue, mynode7,98.56);
    insertPQueue(pqueue, mynode8,34987.4);
    insertPQueue(pqueue, mynode9,7899.99);

    printf("the items of the priority queue are the following: "); 
    
    while(!(isEmpty(pqueue))){
        struct checking min= extractMin(pqueue);
        printf("value with the smallest distance removed and has the value: %f\n", min.distance);
    }

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

TEST_LIST = {
    { "createPQueue", test_createPQueue },
    { "insert", test_insertPQueue },
    { "extractMin", test_extractMin },
    { NULL, NULL }
};
