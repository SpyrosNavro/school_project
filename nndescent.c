#include "header_files/graph.h"
#include "header_files/pqueue.h"



int main(void)
{
    Graph graph;
    const char* filename = "data_structures/5k.txt";
    int nedges = 10;
    int row = 9759;
    int col = 3;
    int flag = 0;
    float distance;
    int* point;
    PQ queue[row], search_queue;
    int neighbor, neighbor_of_neighbor, neighbor_of_reverse;
    int reverse, reverse_of_neighbor, reverse_of_reverse;
    int dest;
    int update, add, add_edge;
    int new_dest, old_dest;
    struct checking new_edges[nedges];
    int temp[row];
    Node search_node;
    struct checking closest;
    struct checking valise[nedges];

    clock_t start, end;
    double time_spent;


    start = clock();
    graph = createGraph(nedges, filename, row, col);
    srand(time(0));    


    // create Priority Queue for every node
    for (int id = 0; id < row; id++)
    {
        queue[id] = createPQueue(row);
    }

    printf("\n\nNNDESCENT\n\n");

    // ITERATIONS
    int iteration = 0;
    do
    {
        printf("iteration %d\n", iteration++);
        add = 0;


        // PUT DISTANCES IN PRIORITY QUEUE
        for (int id = 0; id < row; id++)
        {


            // NEIGHBORS
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



            // REVERSE NEIGHBORS
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


        // INITIALISE REVERSE
        for (int id = 0; id < row; id++)
        {
            temp[id] = 0;
        }

        // UPDATE EDGES
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
                //printf("i:%d old dest: %d\n",i, old_dest);

                for (int j = 0; j < nedges; j++)
                {

                    new_dest = new_edges[j].node->id;

                    //printf("id%d => edge%d %d distance:%f\n", id, j, new_dest, new_edges[j].distance);
                    
                    // 1 edge has stayed the same
                    if (old_dest == new_dest)
                    {
                        //printf("..\n");
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
                    //printf("old:%d new:%d old distance:%f new distance:%f\n", graph->nodes[id]->edges[i]->dest, new_edges[i]->node->id, graph->nodes[id]->edges[i]->distance, new_edges[i]->distance);
                    
                    
                    graph->nodes[id]->edges[i]->src = graph->nodes[id]->id;
                    graph->nodes[id]->edges[i]->dest = new_edges[i].node->id;
                    graph->nodes[id]->edges[i]->distance = new_edges[i].distance;

                    dest = graph->nodes[id]->edges[i]->dest;    

                    //printf("%d nreverse:%d \n",dest, graph->nodes[dest]->nreverse);
                    
                    graph->nodes[dest]->reverse[temp[dest]] = graph->nodes[id]->edges[i];
                    temp[dest]++;
                    //printf("nreverse %d\n", graph->nodes[dest]->nreverse);
                }

                add = 0;

            }
            //printf("n reverse %d\n", graph->nodes[id]->nreverse);
            // if all nodes are the same, STOP ITERATIONS
            if (add == row)
            {
                flag = 1;
                break;
            }

        
        }
        
        if (flag == 0)
        {
            for (int id = 0; id < row; id++)
            {
                graph->nodes[id]->nreverse = temp[id];
            }
        }

    } while (flag == 0);



    printf("\nFINAL\n");
    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < nedges; i++)
        {
            printf("id %d => %d\n", graph->nodes[id]->id, graph->nodes[id]->edges[i]->dest);
            
        }
    }

    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < graph->nodes[id]->nreverse; i++)
        {
            printf("id %d has reverse neighbor %d\n", graph->nodes[id]->id, graph->nodes[id]->reverse[i]->src);
        }
    }

    // free queue
    for (int id = 0; id < row; id++)
    {
        destroyPQueue(queue[id]);
    }



    flag = 0;
    add = 0;

    // random point for search
    point = malloc(graph->dim * sizeof(*point));
    search_node = malloc(sizeof(*search_node));
    for (int i = 0; i < graph->dim; i++)
    {
        point[i] = rand()%21;
    }
    search_node->coord = point;

    // we start from this random node of the graph
    int seed = rand()%row;

    // create Priority Queue for search
    search_queue = createPQueue(row);


    printf("\n\n\n");

    // SEARCH K-NEAREST NEIGHBORS
    do
    {

        // insert node[seed] into search_queue
        if (graph->nodes[seed]->checked == 0)
        {
            distance = compute_distance(search_node, graph->nodes[seed], graph->dim);
            //printf("id %d distance: %f\n", graph->nodes[seed]->id, distance);
            insertPQueue(search_queue, graph->nodes[seed], distance);
            graph->nodes[seed]->checked = 1;
        }


        // NEIGHBORS
        for (int neighbors = 0; neighbors < nedges; neighbors++)
        {

            neighbor = graph->nodes[seed]->edges[neighbors]->dest;


            // neighbor
            if (graph->nodes[neighbor]->checked == 1)
            {
                add++;
            }
            else
            {
                distance = compute_distance(search_node, graph->nodes[neighbor], graph->dim);
                //printf("id %d distance: %f\n", graph->nodes[neighbor]->id, distance);
                insertPQueue(search_queue, graph->nodes[neighbor], distance);
                graph->nodes[neighbor]->checked = 1;
            }
        }
    

        // REVERSE NEIGHBORS
        for (int rev = 0; rev < graph->nodes[seed]->nreverse; rev++)
        {

            reverse = graph->nodes[seed]->reverse[rev]->src;


            // reverse neighbor
            if (graph->nodes[reverse]->checked == 1)
            {
                add++;
            }
            else
            {
                distance = compute_distance(search_node, graph->nodes[reverse], graph->dim);
                //printf("id %d distance: %f\n", graph->nodes[reverse]->id, distance);
                insertPQueue(search_queue, graph->nodes[reverse], distance);
                graph->nodes[reverse]->checked = 1;
            }
        }


        // Truncate pool to k-top 
        for (int i = 0; i < nedges; i++)
        {
            valise[i] = extractMin(search_queue);
        }
        destroyPQueue(search_queue);
        search_queue = createPQueue(row);
        for (int i = 0; i < nedges; i++)
        {
            insertPQueue(search_queue, valise[i].node, valise[i].distance);
        }


        closest = valise[0];


        // have we seen all neighbors?
        if (add == nedges + graph->nodes[seed]->nreverse)
        {
            flag = 1;
        }
        add = 0;
        seed = closest.node->id;


    } while (flag == 0);
    




    printf("\nPOINT:"); for (int i = 0; i < graph->dim; i++) { printf("%d ", point[i]); } printf("\n");



    printf("K-NEAREST NODES:\n");

    for (int i = 0; i < nedges; i++)
    {
        for (int j = 0; j < graph->dim; j++)
        {
            printf("%d ", valise[i].node->coord[j]);
        }
        printf(" distance: %f\n", valise[i].distance);
    }
    
    deleteGraph(graph);
    end = clock();
    time_spent = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\nTime needed for action: %fsec\n", time_spent);
    
    return 0;
}