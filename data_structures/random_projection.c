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
    for (int i=0; i< numofNodes; i++){
        printf(" HERE CREATED =%d\n",treen->nodes[i]->id);
    }
    treen->left = NULL;
    treen->right = NULL;
    return treen; 
}


// void create_random_vector(double *randomVector, int dim){
//     for (int i = 0; i < dim; i++)
//     {
//         randomVector[i] = ((double)rand()/RAND_MAX) *2.0 -1.0;
//     }
// }

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
    if (vrows <= 0 || depth <=0){
        return NULL;
    }
    //printf("OUTSIDE numonodes=%d\n",numNodes);

    // create a leaf Tree node, with the graph nodes that consist every leaf
    // if the graph nodes are less than k-edges, this is the Tree leaf node
    if (numNodes <= nedges){
        Node* leafNodes= (Node*)malloc(numNodes * sizeof(Node));
        //printf("numonodes=%d\n",numNodes);
        for (int i = 0; i< numNodes; ++i){
            leafNodes[i] = nodes[i];
            printf("i=%d %d\n",i, leafNodes[i]->id);
            printf("coord=%d %d %d\n", leafNodes[i]->coord[0],leafNodes[i]->coord[1], leafNodes[i]->coord[2]);

            printf("coord=%d %d %d\n", leafNodes[i]->coord[0],leafNodes[i]->coord[1], leafNodes[i]->coord[2]);


        }
        return createTreeNode(leafNodes, numNodes);
        
    }



    // generate random paramentrs and insert inside a vector, to be used for projection computation next
    double* randomVector = (double*)malloc(graph->dim * sizeof(double));
    for (int i = 0; i < graph->dim; i++)
    {
        randomVector[i] = ((double)rand()/RAND_MAX) *2.0 -1.0;
    }        
    
    int pivot =  numNodes/2; 
    printf("pivot = %d\n", pivot);
//    graph->nodes = malloc ( row * sizeof(*(graph->nodes) ));  // allocate array of nodes
    
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

    printf("NUMNODES= %d\n\n\n", numNodes); 
    
    // for every point of the graph, check the projection and place it, eather or the left, or the right 
    for (int i=0; i < numNodes; ++i){
        // use as threshold the projection of the root 
        double projection = randrom_projection(nodes[i], randomVector, graph->dim);
        if (projection < randrom_projection(nodes[pivot], randomVector, graph->dim)){
            leftNodes[leftCounter++] = nodes[i];
            for (int j = 0; j < columns; j++)
            {
                leftNodes[i]->coord[j] = nodes[i]->coord[j];
            }
        //    printf("inside left\n");
        //    printf("i=%d %d\n",i, nodes[i]->id);
        //    printf("coord=%d %d %d\n", leftNodes[i]->coord[0],nodes[i]->coord[1], nodes[i]->coord[2]);
        //    printf("leftcounter=%d", leftCounter);

        }
        else {
            rightNodes[rightCounter++] = nodes[i];
            for (int j = 0; j < columns; j++)
            {
                rightNodes[i]->coord[j] = nodes[i]->coord[j];
            }
        //    printf("inside right\n");

        //    printf("i=%d %d\n",i, nodes[i]->id);
        //    printf("coord=%d %d %d\n", rightNodes[i]->coord[0],nodes[i]->coord[1], nodes[i]->coord[2]);
        //    printf("rightounter=%d", rightCounter);


        }
    }

    TreeNode* treen = createTreeNode(NULL, 0); // new node for the pivot
    // build left and right subtrees recursively 
                                                        
    treen->left = createRandomProjectionTree(leftNodes, graph, vrows, columns,depth, D, leftCounter, nedges);
    treen->right = createRandomProjectionTree(rightNodes, graph,vrows,columns, depth, D, rightCounter, nedges);


    free(randomVector);
    return treen; 
}

void initializeLeafNodes(TreeNode* root, Graph graph, int D, int nedges){
    if (root != NULL){
        if (root->left == NULL && root->right == NULL){  // leaf of the RPTree
            // so we connect the points within this leaf node
            connectGraphEdges(root, graph, root->numofNodes, nedges);

        }
        else {
            // traverse the RPTree, go to the left and right subtrees
            initializeLeafNodes(root->left, graph, D, nedges);
            initializeLeafNodes(root->right, graph,D, nedges);
        }
    }
}

void connectGraphEdges(TreeNode* leafNode, Graph graph, int numNodes, int nedges){
    
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
        printf("TESTING:\n");
        printf("leaf node =%d\n", leafNode->nodes[id]->id);

        for(int j=0; j< numNodes; j++){
            printf(" with:");
            printf("leaf node =%d\n", leafNode->nodes[j]->id); 
            if(searchPQueue(queue[id],leafNode->nodes[j]) != 0){
                if (id != j){
                    distance = euclideanDistance(leafNode->nodes[id],leafNode->nodes[j], graph->dim);
                    insertPQueue(queue[id], leafNode->nodes[j], distance);
                    printf("inserting=%d\n", leafNode->nodes[id]->id ,"into queue",id);
                    //graph->nodes[id]->edges = j;
                    insertPQueue(queue[j], leafNode->nodes[id], distance);
                    printf("inserting=%d\n", leafNode->nodes[j]->id ,"into queue",j);

                    
                }
            }
        }
        

    }
}

// void get_all_edges(){
//     if(searchPQueue(queue[id],leafNode->nodes[j]) != 0){

//     }

// }

void free_graph(Graph graph){
    for (int i = 0; i < graph->nnodes - 1; i++)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            free(graph->nodes[i]->edges[j]);
        }
        free(graph->nodes[i]);
    }
    free(graph);

}


void free_RandomProjectionTree( TreeNode* treen){


    if(treen == NULL){
        return;
    }
    free_RandomProjectionTree(treen->left);
    free_RandomProjectionTree(treen->right);
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
    int D = 3;
    int depth =2;
 
    Graph graph= initializeRPTreeGraph(nedges, filename, row, column, treeDepth, D);
     
    for (int i=0; i<D; i++){
        TreeNode* treen;
        treen = createRandomProjectionTree(graph->nodes, graph, row,column, depth, D, row, nedges);
         
        initializeLeafNodes(treen, graph, D, nedges);
        // Free the allocated memory

    

   
        free_RandomProjectionTree(treen);

    }
    free(graph);
    return 0;
} 

