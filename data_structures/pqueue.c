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




struct PQueue* createPQueue(int capacity){
    
    struct PQueue* pqueue= (struct PQueue* )malloc(sizeof(struct PQueue));
    pqueue->capacity= capacity;
    pqueue->size= 0;
    pqueue->array= (struct checking* )malloc(capacity* sizeof(struct checking));

    //printf("created a pqueue with capacity= %d\n", pqueue->capacity);
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

// search returns 0 if the node belongs in the queue, and 1 if if not 
int searchPQueue(struct PQueue* pqueue, Node node){
    for (int i=0; i<pqueue->size; i++){
        
        if(node->id == pqueue->array[i].node->id){
            //printf("id=%d\n",pqueue->array[i].node->id);
            return 0;
        }
    }
    return 1;
}
 

int isEmpty(struct PQueue* pqueue){
    return (pqueue->size == 0);

}

void destroyPQueue(struct PQueue* pqueue){

    free(pqueue->array);
    free(pqueue);
}