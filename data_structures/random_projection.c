#include "../header_files/graph.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
  
#include "../header_files/pqueue.h"
#include "../header_files/random_projection.h"

// if the same pair of points fall into the same leaf node in most rpTrees, they will be connected as k-neighbors



Graph initializeRPTreeGraph (int nedges, const char *file_name, int row, int column, int depth, int D) 
{
    Graph graph = malloc(sizeof(*graph));
    graph->nodes = malloc ( row * sizeof(*(graph->nodes) ));  // allocate array of nodes
    int dest;

    int** data = import_data(file_name, row);
    
    graph->dim = column;
    graph->nnodes = row;
    graph->neighbors = nedges;
    printf("CREATE GRAPH\n\n");

    // initialise NODES
    for (int id = 0; id < row; id++)
    {   
        graph->nodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
        graph->nodes[id]->id = id;
        graph->nodes[id]->reverse = malloc ( row * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
        graph->nodes[id]->nreverse = 0;
        graph->nodes[id]->checked = 0;
        graph->nodes[id]->same = 0;
        graph->nodes[id]->coord = malloc( column * sizeof(*(graph->nodes[id]->coord)) );
        // fill all the nodes coordinations 
        for (int j = 0; j < column; j++)
        {
            graph->nodes[id]->coord[j] = data[id][j];
        }

        // initialize edges 

        // add directed edges to each node
        graph->nodes[id]->edges = malloc ( nedges * sizeof(*(graph->nodes[id]->edges)) );

        for (int j = 0; j < nedges; j++)
        {
            graph->nodes[id]->edges[j] = malloc(sizeof( *(graph->nodes[id]->edges[j]) ));  // allocate edge
            graph->nodes[id]->edges[j]->src = id;
            graph->nodes[id]->edges[j]->is = true;
            graph->nodes[id]->edges[j]->rev_is = true;


        }
    
    
    }

    
    return graph;
}

// create a new tree node
TreeNode* createTreeNode(Node* nodes, int numofNodes){    // create a leaf node, doesn't have other left, right 
    TreeNode* treen = (TreeNode* )malloc(sizeof(TreeNode));
    treen->nodes = nodes; 
    treen->numofNodes = numofNodes;
    // for (int i=0; i< numofNodes; i++){
    //     printf(" HERE CREATED =%d\n",treen->nodes[i]->id);
    // }
    treen->left = NULL;
    treen->right = NULL;
    return treen; 
}



// function that performs random projection value, for every node of the graph , given random parametres
double randrom_projection(Node node, double *randomVector, int dim){
    double sum = 0.0;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum + node->coord[i] * randomVector[i];
    }
    return sum; 
}
 

TreeNode* createRandomProjectionTree(Node* nodes, Graph graph, int vrows,int columns, int depth, int D, int numNodes, int nedges){

//    printf("INSIDE CREATE RANDOM PROJECTION \n\n");
    
        if (vrows <= 0 || depth <=0){
            return NULL;
        }

        if (numNodes <= nedges ){
            Node* leafNodes = (Node*)malloc(numNodes * sizeof(Node));
          
            for (int i = 0; i< numNodes; i++){
                leafNodes[i] = nodes[i];
                //printf("id= %d\n", leafNodes[i]->id);
            }
            return createTreeNode(leafNodes, numNodes);
            
        }
        // D is a given parameter 
        if(numNodes > D ){
        // generate random paramentrs and insert inside a vector, to be used for projection computation next
            double* randomVector = (double*)malloc(graph->dim * sizeof(double));
            for (int i = 0; i < graph->dim; i++){
                
                randomVector[i] = ((double)rand()/RAND_MAX) *2.0 -1.0;
            }        
        
            int pivot =  numNodes/2; 
        
            int leftCounter = 0;
            int rightCounter = 0; 
            Node* leftNodes= (Node*)malloc(numNodes * sizeof(Node));
            Node* rightNodes= (Node*)malloc(numNodes * sizeof(Node));

        
            for( int id =0; id < numNodes; id++){
                leftNodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
                leftNodes[id]->reverse = malloc (numNodes * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
                leftNodes[id]->nreverse = 0;
                leftNodes[id]->checked = 0;
                leftNodes[id]->same = 0;
                leftNodes[id]->coord = malloc( columns * sizeof(*(graph->nodes[id]->coord)) );

                rightNodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
                rightNodes[id]->reverse = malloc (numNodes * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
                rightNodes[id]->nreverse = 0;
                rightNodes[id]->checked = 0;
                rightNodes[id]->same = 0;
                rightNodes[id]->coord = malloc( columns * sizeof(*(graph->nodes[id]->coord)) );

            }
        
        
            // for every point of the graph, check the projection and place it, eather or the left, or the right 
            for (int i=0; i < numNodes; i++){
                // use as threshold the projection of the root 
                double projection = randrom_projection(nodes[i], randomVector, graph->dim);
                if (projection < randrom_projection(nodes[pivot], randomVector, graph->dim)){
                    leftNodes[leftCounter++] = nodes[i];
                    for (int j = 0; j < columns; j++)
                    {
                        leftNodes[i]->coord[j] = nodes[i]->coord[j];
                    }

                }
                else {
                    rightNodes[rightCounter++] = nodes[i];
                    for (int j = 0; j < columns; j++)
                    {
                        rightNodes[i]->coord[j] = nodes[i]->coord[j];
                    }
                }
            }
        
            TreeNode* treen = createTreeNode(NULL, 0); // new node for the pivot
            // build left and right subtrees recursively 
                                                 
            treen->left = createRandomProjectionTree(leftNodes, graph, vrows, columns,depth, D, leftCounter, nedges);                                                 
            treen->right = createRandomProjectionTree(rightNodes, graph,vrows,columns, depth, D, rightCounter, nedges);
                       
            free(randomVector);
            return treen; 
    }
    return;
}

void initializeLeafNodes(TreeNode* root, Graph graph, int D, int nedges, int vrows){
    if (root != NULL){
        if (root->left == NULL && root->right == NULL){  // leaf of the RPTree
            // so we connect the points within this leaf node
            connectGraphEdges(root, graph, root->numofNodes, nedges, vrows);

        }
        else {
            // traverse the RPTree, go to the left and right subtrees
            initializeLeafNodes(root->left, graph, D, nedges, vrows);
            initializeLeafNodes(root->right, graph,D, nedges, vrows);
        }
    }
}

void connectGraphEdges(TreeNode* leafNode, Graph graph, int numNodes, int nedges, int vrows){
     
    PQ queue[numNodes];
    // create a Priority Queue for every node of the leaf node
    for (int id = 0; id < numNodes; id++)
    {
        queue[id] = createPQueue(numNodes);
    }
    
    for (int id = 0; id < numNodes; id++)
    {
        // for every node of the leaf node, compute the distance and insert it inside the queue
        float distance = 0;
        // printf("leaf node =%d\n", leafNode->nodes[id]->id);
        for(int j=0; j< numNodes; j++){
                if (id != j){
                    distance = euclideanDistance(leafNode->nodes[id],leafNode->nodes[j], graph->dim); 
                    insertPQueue(queue[id], leafNode->nodes[j], distance);
                    
                }
            
        }

        struct checking results[nedges];
            
        // get the k nearest for every node
        for(int i = 0; i < nedges; i++){
            if(isEmpty(queue[id])!=0 ){
                results[i] = extractMin(queue[id]);

            }
        }

        // if there isnt 
        if ( results!=NULL){

            // get the k nearest for every node      
            for (int j = 0; j < nedges; j++){
                
                graph->nodes[leafNode->nodes[id]->id]->edges[j]->src =  leafNode->nodes[id]->id;
                if(j < numNodes-1){ 
                    
                    graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest = results[j].node->id; 
        
                    printf("the node with id = %d\n", leafNode->nodes[id]->id); 
                    printf("has neighbors = \n");
                    printf("destination of = %d \n",graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest);
                    //printf("with coordinates: %d\n", graph->nodes[graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest]->coord[0]);
                    graph->nodes[leafNode->nodes[id]->id]->edges[j]->distance = results[j].distance;
   
                    int dest = graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest;
                    graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = leafNode->nodes[id]->edges[j];
                    //printf("reverse = %d\n", graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse]->src);

                    graph->nodes[results[j].node->id]->nreverse++; 

                }
                else {
                    
                    int dest;
                    do {
                        // rand in range [0, rows-1]
                        // rand() % (max_number + 1 - minimum_number) + minimum_number
                        graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest = rand()%vrows;

                        dest = graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest;
                    }while ( (dest == id) || (dest < 0) || (dest >= graph->nnodes) );
  
                    printf("the node with id = %d\n", leafNode->nodes[id]->id); 
                    printf("has neighbors = \n");
                    printf("destination of  = %d \n",graph->nodes[leafNode->nodes[id]->id]->edges[j]->dest);
                    graph->nodes[leafNode->nodes[id]->id]->edges[j]->distance = euclideanDistance(graph->nodes[leafNode->nodes[id]->id], graph->nodes[dest], graph->dim);    
                    graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = leafNode->nodes[id]->edges[j];
                    graph->nodes[dest]->nreverse++; 
                }
                
            }

        }
        else {
            printf("EMPTY QUEUE WITH ID=%d\n\n\n", leafNode->nodes[id]->id);
        }

    }

    for (int i=0; i<numNodes; i++){
        destroyPQueue(queue[i]);
    }
}


void free_graph(Graph graph){
    for (int i = 0; i < graph->nnodes; i++)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            free(graph->nodes[i]->edges[j]);
        }
        free(graph->nodes[i]->reverse);
        free(graph->nodes[i]->coord);
        free(graph->nodes[i]->edges);
        free(graph->nodes[i]);
    }
    free(graph->nodes);

    free(graph);

}


void free_RandomProjectionTree( TreeNode* treen, int nedges){
    for (int i = 0; i < treen->numofNodes; i++)
    {
        for (int j = 0; j < nedges; j++)
        {
            free(treen->nodes[i]->edges[j]);
        }
       
        free(treen->nodes[i]->reverse);
        free(treen->nodes[i]->coord);
        free(treen->nodes[i]->edges);
        free(treen->nodes[i]);
    }

    if(treen == NULL){
        return;
    }
    if(treen->left !=NULL){
        free_RandomProjectionTree(treen->left,nedges);
    }
    if(treen->right){
        free_RandomProjectionTree(treen->right, nedges);
    }
    free(treen->nodes);
    free(treen);

}

int main() {
    
    // Build a random projection tree
    int treeDepth = 3;
    // TreeNode* root = buildRandomProjectionTree( );

    // Initialize a directed graph from the random projection tree
    int nedges = 2;
    int row = 10;
    int column = 3;
    const char* filename = "small.txt";
    int D = 2;
    int depth =2;
 
    Graph graph= initializeRPTreeGraph(nedges, filename, row, column, treeDepth, D);
     
    //for (int i=0; i<D; i++){
        TreeNode* treen;
        treen = createRandomProjectionTree(graph->nodes, graph, row,column, depth, D, row, nedges);
        
        initializeLeafNodes(treen, graph, D, nedges, row);
        // Free the allocated memory
 
        free_RandomProjectionTree(treen, nedges);

    //}
    free(graph);
    return 0;
} 

