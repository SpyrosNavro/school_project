#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "../header_files/graph.h"

#pragma once

// partitioninig of the data to the right, and to the left side
typedef struct TreeNode {
    Node* nodes;
    int numofNodes; 
    struct TreeNode* left;  
    struct TreeNode* right;
 } TreeNode;

Graph initializeRPTreeGraph (int nedges, const char *file_name, int row, int column, int depth, int D);
TreeNode* createTreeNode(Node* nodes, int numofNodes);
double randrom_projection(Node node, double *randomVector, int dim);
TreeNode* createRandomProjectionTree(Node* nodes, Graph graph, int vrows,int columns, int depth, int D, int numNodes, int nedges);
void initializeLeafNodes(TreeNode* root, Graph graph, int D, int nedges, int vrows);
void connectGraphEdges(TreeNode* leafNode, Graph graph, int numNodes, int nedges, int vrows);
void free_graph(Graph graph);
void free_RandomProjectionTree( TreeNode* treen, int nedges);

