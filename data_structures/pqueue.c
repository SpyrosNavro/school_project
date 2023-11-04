#include <stdio.h>
#include <stdlib.h>
#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "assert.h"


// implementation with min heap -> the parent is allways smaller than the children 
// indexing of the array that implements the heap 

// parent(i)=(i-1)/2  -> parent node 
// left_child(i)=2*i+1 -> left child
// right_child(i)=2*i +2 -> right child 

typedef struct node* Node;

struct node {
    int id;    // id of point 
    //int* coord;  // coordinates of n-dimentional point
    //Edge* edges;
    // struct Node* next;  not useful for now
};

struct checking{   // the nodes that are checked, and have been put inside the queue 
    Node node; 
    float distance; 
};

struct PQueue{
    struct checking* array;
    int capacity; 
    int size;
};

struct PQueue* createPQueue(int capacity){
    
    struct PQueue* pqueue= (struct PQueue* )malloc(sizeof(struct PQueue));
    pqueue->capacity= capacity;
    pqueue->size= 0;
    pqueue->array= (struct checking* )malloc(capacity* sizeof(struct checking));

    printf("created a pqueue with capacity= %d\n", pqueue->capacity);
    return pqueue; 
}

// swapping two nodes of the pqueue - neighbors 
void swap(struct checking* a, struct checking* b){
    struct checking temp= *a;
    *a=*b;
    *b=temp;
    //printf(" JUSTTT swapped a=%f\n and b=%f\n", a->distance,b->distance);
}

// heapify a tree, with given root
// after we exrtract, we put the last element from the tree ,in the root of the tree
// then heapify, puts it in the right position 
void heapify(struct PQueue* pqueue, int root){
    
    int small = root; 
    int left = 2*root+1;
    int right = 2*root+2;

    if (left< pqueue->size && pqueue->array[left].distance < pqueue->array[small].distance ){
        small = left;
    }
    if (right< pqueue->size && pqueue->array[right].distance < pqueue->array[small].distance ){
        small = right;
    }
    if (small != root){
        swap(&pqueue->array[root], &pqueue->array[small]);
        heapify(pqueue, small);
    }
}

// insert the node and the distance inside the priority queue
// the node inserts on the end of the tree, and then it goes up depending on the smallest distance
void insertPQueue(struct PQueue* pqueue, Node node, float distance){
    if (pqueue->size == pqueue->capacity){
        //printf("Cannot enter another value to the queue. It is full");
        return;
    }
    
    int i=pqueue->size++;
    
    pqueue->array[i].node= node; //  
    pqueue->array[i].distance= distance; 
    
    //printf("inserting node with distance=%f\n",pqueue->array[pqueue->size].distance);


    
    // **** maybe i could do heapify 
    while (i>0 &&  pqueue->array[i].distance < pqueue->array[(i-1)/2].distance){   // move the smallest element on the top , if it is smaller than the parent
        //printf("swapping a=%f\n and b=%f\n", pqueue->array[i].distance, pqueue->array[i].distance);
        swap(&pqueue->array[i],&pqueue->array[(i-1)/2]);
        i =(i-1)/2;    // if the switch happens, then the index changes, to go up in the tree
    }
    //printf("inserting completed");
    //printf("inserting node with distance=%f\n",pqueue->array[pqueue->size].distance);

}


// extract the minimum value - the node with the smallest distance
struct checking extractMin(struct PQueue* pqueue){
    if(pqueue->size <=0){
        printf("Empty priority queue, cannot extract minimum distance");
        //return;    //** has to be an empty node struct type
    }
    if (pqueue->size ==1){
        pqueue->size--;
        return pqueue->array[0];
    }
    struct checking min= pqueue->array[0];
    pqueue->array[0] = pqueue->array[pqueue->size-1];    // we put in the root the last element 
    pqueue->size--;
    heapify(pqueue, 0);               // then the heapify puts it in the right position
    
                  

    return min;
}

int isEmpty(struct PQueue* pqueue){
    printf("pqueue->size=%d\n",pqueue->size);
    return (pqueue->size == 0);

}

void destroyPQueue(struct PQueue* pqueue){

    free(pqueue->array);
    free(pqueue);
}

void test_createPQueue(){
    struct PQueue* pqueue = createPQueue(10);
    TEST_ASSERT(pqueue->capacity==10);
    TEST_ASSERT(pqueue !=NULL);
    TEST_ASSERT(pqueue->size==0);

    destroyPQueue(pqueue);
}
/*
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

    printf("the items of the priority queue are the following: ");
    //struct checking min=  (struct checking)malloc(sizeof(struct checking));
}

void test_extractMin(){

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
    




    //return 0;
}
*/
TEST_LIST = {
    { "createPQueue", test_createPQueue },
    //{ "insert", test_insertPQueue },
    //{ "extractMin", test_extractMin },

    { NULL, NULL }
};