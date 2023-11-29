#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "../header_files/nnd_functions.h"





void check_neighbors(Graph graph, int id, PQ queue[])
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

            distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_neighbor], graph->dim);
            
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

            distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_neighbor], graph->dim);
            
            // search
            if (searchPQueue(queue[id], graph->nodes[reverse_of_neighbor]) == 1) {
            insertPQueue(queue[id], graph->nodes[reverse_of_neighbor], distance); }


            if (searchPQueue(queue[reverse_of_neighbor], graph->nodes[id]) == 1) {
            insertPQueue(queue[reverse_of_neighbor], graph->nodes[id], distance); }
        }
    }
}





void check_reverse_neighbors(Graph graph, int id, PQ queue[])
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

            distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_reverse], graph->dim);


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

            distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_reverse], graph->dim);
            
            // search
            if (searchPQueue(queue[id], graph->nodes[reverse_of_reverse]) == 1) {
            insertPQueue(queue[id], graph->nodes[reverse_of_reverse], distance); }
            

            if (searchPQueue(queue[reverse_of_reverse], graph->nodes[id]) == 1) {
            insertPQueue(queue[reverse_of_reverse], graph->nodes[id], distance); }
        }
    }
}





int update_edges(PQ queue[], Graph graph, int row, int nedges, int temp[])
{
    struct checking new_edges[nedges];
    int update, add_edge, old_dest, new_dest, dest, add;
    add = 0;

    for (int id = 0; id < row; id++)
    {
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
                }
            }
            
            // if there is an update then go update the edges
            if (update == 1) break;

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

                dest = graph->nodes[id]->edges[i]->dest;    

                
                graph->nodes[dest]->reverse[temp[dest]] = graph->nodes[id]->edges[i];
                temp[dest]++;
            }

            add = 0;

        }

        // if all nodes are the same, STOP ITERATIONS
        if (add == row)
        {
            return 1;
        }
    }


    return 0;
}





void search_neighbors(Graph graph, PQ search_queue, Node search_node, int seed, int nedges, int* add)
{
    int distance, neighbor;

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
            distance = compute_distance(search_node, graph->nodes[neighbor], graph->dim);

            insertPQueue(search_queue, graph->nodes[neighbor], distance);
            graph->nodes[neighbor]->checked = 1;
        }
    }
}





void search_reverse_neighbors(Graph graph, PQ search_queue, Node search_node, int seed, int* add)
{
    int reverse, distance;

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
            distance = compute_distance(search_node, graph->nodes[reverse], graph->dim);

            insertPQueue(search_queue, graph->nodes[reverse], distance);
            graph->nodes[reverse]->checked = 1;
        }
    }
}