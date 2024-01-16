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