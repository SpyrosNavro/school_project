#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "../header_files/nnd_functions.h"




void checkNeighbors(Graph graph, int id, PQ queue[])
{
    int neighbor, neighbor_of_neighbor, reverse_of_neighbor;
    float distance;


    for (int neighbors = 0; neighbors < graph->neighbors; neighbors++)
    {
        // neighbor
        neighbor = graph->nodes[id]->edges[neighbors]->dest;
        

        if (searchPQueue(queue[id], graph->nodes[neighbor]) == 1) {
        insertPQueue(queue[id], graph->nodes[neighbor], graph->nodes[id]->edges[neighbors]->distance); }


        if (searchPQueue(queue[neighbor], graph->nodes[id]) == 1) {
        insertPQueue(queue[neighbor], graph->nodes[id], graph->nodes[id]->edges[neighbors]->distance); }
        

        // neighbor of neighbor
        for (int i = 0; i < graph->neighbors; i++)
        {
            neighbor_of_neighbor = graph->nodes[neighbor]->edges[i]->dest;
            
            if (id == neighbor_of_neighbor) continue;

            distance = euclideanDistance(graph->nodes[id], graph->nodes[neighbor_of_neighbor], graph->dim);
            printf("distance in check_neigh = %f\n\n\n", distance);
            // search
            if (searchPQueue(queue[id], graph->nodes[neighbor_of_neighbor]) == 1) {
            insertPQueue(queue[id], graph->nodes[neighbor_of_neighbor], distance); }


            if (searchPQueue(queue[neighbor_of_neighbor], graph->nodes[id]) == 1) {
            insertPQueue(queue[neighbor_of_neighbor], graph->nodes[id], distance); }
        }


        // reverse neighbor of neighbor
        for (int i = 0; i < graph->nodes[neighbor]->nreverse; i++)
        {
            reverse_of_neighbor = graph->nodes[neighbor]->reverse[i]->src;

            if (id == reverse_of_neighbor) continue;

            distance = euclideanDistance(graph->nodes[id], graph->nodes[reverse_of_neighbor], graph->dim);
            printf("distance in 2 = %f\n\n\n", distance);
            
            // search
            if (searchPQueue(queue[id], graph->nodes[reverse_of_neighbor]) == 1) {
            insertPQueue(queue[id], graph->nodes[reverse_of_neighbor], distance); }


            if (searchPQueue(queue[reverse_of_neighbor], graph->nodes[id]) == 1) {
            insertPQueue(queue[reverse_of_neighbor], graph->nodes[id], distance); }
        }
    }
}





void checkReverse(Graph graph, int id, PQ queue[])
{
    int reverse, neighbor_of_reverse, reverse_of_reverse;
    float distance;


    for (int rev = 0; rev < graph->nodes[id]->nreverse; rev++)
    {
        // reverse neighbor
        reverse = graph->nodes[id]->reverse[rev]->src;
        
        
        if (searchPQueue(queue[id], graph->nodes[reverse]) == 1) {
        insertPQueue(queue[id], graph->nodes[reverse], graph->nodes[id]->reverse[rev]->distance); }


        if (searchPQueue(queue[reverse], graph->nodes[id]) == 1) {
        insertPQueue(queue[reverse], graph->nodes[id], graph->nodes[id]->reverse[rev]->distance); }


        // neighbors of reverse neighbor
        for (int i = 0; i < graph->neighbors; i++)
        {
            neighbor_of_reverse = graph->nodes[reverse]->edges[i]->dest;

            if (id == neighbor_of_reverse) continue;

            distance = euclideanDistance(graph->nodes[id], graph->nodes[neighbor_of_reverse], graph->dim);


            if (searchPQueue(queue[id], graph->nodes[neighbor_of_reverse]) == 1) {
            insertPQueue(queue[id], graph->nodes[neighbor_of_reverse], distance); }


            if (searchPQueue(queue[neighbor_of_reverse], graph->nodes[id]) == 1) {
            insertPQueue(queue[neighbor_of_reverse], graph->nodes[id], distance); }
            
        }


        // reverse neighbors of reverse neighbor
        for (int i = 0; i < graph->nodes[reverse]->nreverse; i++)
        {
            reverse_of_reverse = graph->nodes[reverse]->reverse[i]->src;

            if (id == reverse_of_reverse) continue;

            distance = euclideanDistance(graph->nodes[id], graph->nodes[reverse_of_reverse], graph->dim);
            printf("distance in 3 = %f\n\n\n", distance);
            

            // search
            if (searchPQueue(queue[id], graph->nodes[reverse_of_reverse]) == 1) {
            insertPQueue(queue[id], graph->nodes[reverse_of_reverse], distance); }
            

            if (searchPQueue(queue[reverse_of_reverse], graph->nodes[id]) == 1) {
            insertPQueue(queue[reverse_of_reverse], graph->nodes[id], distance); }
        }
    }
}





int updateEdges(PQ queue[], Graph graph, int row, int nedges)
{
    struct checking new_edges[nedges];
    int update, add_edge, old_dest, new_dest, add, total_changes;
    add = 0;
    


    total_changes = 0; // changes of every egde, in total 
    for (int id = 0; id < row; id++)
    {
        graph->nodes[id]->nreverse = 0;
        // get new edges
        for(int i = 0; i < nedges; i++)
        {
            new_edges[i] = extractMin(queue[id]);
        }


        // check if new edges == old edges
        update = 0;
        add_edge = 0;
        for (int i = 0; i < nedges; i++)
        {
            old_dest = graph->nodes[id]->edges[i]->dest;

            for (int j = 0; j < nedges; j++)
            {

                new_dest = new_edges[j].node->id;

                
                // 1 edge has stayed the same
                if (old_dest == new_dest)
                {
                    add_edge++;
                    break;
                }

                // found an update
                if ( (j == nedges - 1) && (old_dest != new_dest) )
                {
                    update = 1;
                    total_changes++;
                }
            }
            
            // if there is an update then go update the edges
            //if (update == 1) break;

        }


        // if all edges of a node are the same then one node has stayed the same
        if (add_edge == nedges)
        {
            add++;
        }

        add_edge = 0;


        // if any change has been found UPDATE edges of node[id]
        if (update == 1)
        {
            for (int i = 0; i < nedges; i++)
            {   
                graph->nodes[id]->edges[i]->src = graph->nodes[id]->id;
                graph->nodes[id]->edges[i]->dest = new_edges[i].node->id;
                graph->nodes[id]->edges[i]->distance = new_edges[i].distance;
            }

            add = 0;

        }

        // if all nodes are the same, STOP ITERATIONS
        // if (add == row)
        // {
        //     return 1;
        // }

        if (add == row)
        {
            return 0;  
        }
    }

    printf("TOTAL CHANGES IN UPDATE=%d\n",total_changes);
    return total_changes;
}




void searchNeighbors(Graph graph, PQ search_queue, Node search_node, int seed, int nedges, int* add)
{
    int  neighbor;
    float distance;

    for (int neighbors = 0; neighbors < nedges; neighbors++)
    {

        neighbor = graph->nodes[seed]->edges[neighbors]->dest;


        // neighbor
        if (graph->nodes[neighbor]->checked == 1)
        {
            (*add)++;
        }
        else
        {
            distance = euclideanDistance(search_node, graph->nodes[neighbor], graph->dim);
            printf("DISTANCE IN SEARCH NEGHBOR = %f", distance);
            insertPQueue(search_queue, graph->nodes[neighbor], distance);
            graph->nodes[neighbor]->checked = 1;
        }
    }
}

 



void searchReverse(Graph graph, PQ search_queue, Node search_node, int seed, int* add)
{
    int reverse;
    float distance;

    for (int rev = 0; rev < graph->nodes[seed]->nreverse; rev++)
    {

        reverse = graph->nodes[seed]->reverse[rev]->src;


        // reverse neighbor
        if (graph->nodes[reverse]->checked == 1)
        {
            (*add)++;
        }
        else
        {
            distance = euclideanDistance(search_node, graph->nodes[reverse], graph->dim);
            printf("distance in 5= %f\n\n\n", distance);


            insertPQueue(search_queue, graph->nodes[reverse], distance);
            graph->nodes[reverse]->checked = 1;
        }
    }
}

// void brute_force(Graph graph, int row, Node search_node, int nedges){
    
//     PQ queue[row];
//     for (int id = 0; id < row; id++)
//     {
//         queue[id] = createPQueue(row);
//     }
//     printf("\nSEARCH NODE INSIDE BRUTE FORCE:"); for (int i = 0; i < graph->dim; i++) { printf("%d ", search_node->coord[i]); } printf("\n");

//     float distance;
//     // with the given graph, we take 
//     for (int id = 0; id < row; id++)
//     { 
//         distance = compute_distance(search_node,graph->nodes[id], graph->dim);
//         //printf("distance computed %f=",distance);
//         insertPQueue(search_queue, graph->nodes[id], distance);

//     }
//     struct checking results[nedges];
//     printf("RESULTS FROM BRUTE FORCE:\n");
//     printf("nedges=%d\n",nedges);
//     for (int i = 0; i < nedges; i++){   
//         results[i] = extractMin(search_queue);
//         printf("distance EXTRACTED %f=",results[i].distance);
//     }

//     for (int i = 0; i < nedges; i++)
//     {
//         for (int j = 0; j < graph->dim; j++)
//         {
//             printf("%d ", results[i].node->coord[j]);
//         }
//         printf(" distance: %f\n", results[i].distance);
//     }
//     destroyPQueue(search_queue);
// }

void brute_force_algorithm(Graph graph, int row, int nedges){

    printf("in brute force");
    PQ queue[row];
    // create a Priority Queue for every node
    for (int id = 0; id < row; id++)
    {
        queue[id] = createPQueue(row);
    }
    float distance=0.0; 
    for (int id = 0; id < row; id++)
    {   
        for(int j=0; j< row; j++){
            if(searchPQueue(queue[id],graph->nodes[j] ) != 0){
                if (id != j){
                    distance = euclideanDistance(graph->nodes[id],graph->nodes[j], graph->dim);
                    //printf("distance computed BRUTE FORCE =%f\n",distance);
                    insertPQueue(queue[id], graph->nodes[j], distance);
                    insertPQueue(queue[j], graph->nodes[id], distance);
                    
                }
            }
        }
        
    }
    struct checking results[nedges];
//    printf("RESULTS FROM BRUTE FORCE:\n");

    int correctNeighbors=0;
    int totalNeighbors= nedges*row;
    int nn_edge, brute_edge;
    for (int id = 0; id < row; id++){
        // get the k nearest for every node
        for(int i = 0; i < nedges; i++){
            results[i] = extractMin(queue[id]);

        }

        // get the k nearest for every node
    
        // check if real edges == nnedges
        for (int i = 0; i < nedges; i++){
            nn_edge = graph->nodes[id]->edges[i]->dest;
            
            // same edge 
            
            for (int j = 0; j < nedges; j++){

                brute_edge = results[j].node->id;

                if (nn_edge == brute_edge){
                    // found the correct 
                    correctNeighbors++;
                }

            }

        }
        

    }
    
    double percentageSuccess = ((double)correctNeighbors / totalNeighbors) * 100;
    printf("Percentage of Success: %f\n", percentageSuccess);

    for (int i=0; i<row; i++){
        destroyPQueue(queue[i]);
    }
    
}  

// float p = 0.5;
// int pk = p * nedges; // until pk
// int checked =0; 
// // create a 
// //for every id 
// 
// true_flags = graph->nodes[id]->edges->number_of_true;
// bool sum_of_flags = 
// for (int i = 0; i < nedges; i++){
//     if( graph->nodes[id]->edges->flag = true){

//     }
// }

// while(checked < pk || checked == true_flags){
//     // choose random 
//     int random = rand()%row;

//     do the local join
//     checked++;
//   

//     

//     flag= false; // checked this node 
// }






