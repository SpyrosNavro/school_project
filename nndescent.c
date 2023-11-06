#include "header_files/graph.h"
#include "header_files/pqueue.h"



int main(void)
{
    Graph graph;
    const char* filename = "data_structures/small.txt";
    int nedges = 2;
    int row = 5;
    int col = 3;
    int flag = 0;
    float distance;
    int* point;
    int* start;
    PQ queue[row];
    int neighbor, neighbor_of_neighbor, neighbor_of_reverse;
    int reverse, reverse_of_neighbor, reverse_of_reverse;
    int dest;
    int update, add, add_edge;
    int new_dest, old_dest;
    //struct checking temp;
    struct checking new_edges[nedges];



    graph = createGraph(nedges, filename, row, col);
    point = malloc(graph->dim * sizeof(*point));
    srand(time(0));


    printf("ooh look at the friendly locals. HOLA!\n");
    // random point for search
    for (int i = 0; i < graph->dim; i++)
    {
        point[i] = rand();
    }


    // create Priority Queue for every node
    for (int id = 0; id < row; id++)
    {
        queue[id] = createPQueue(row);
    }

    printf("\n\nNNDESCENT\n\n");

    // ITERATIONS
    do
    {
        add = 0;


        // PUT DISTANCES IN PRIORITY QUEUE
        for (int id = 0; id < row; id++)
        {


            // NEIGHBORS
            for (int neighbors = 0; neighbors < graph->neighbors; neighbors++)
            {
                // neighbor
                //printf(" MY ID =%d\n", id);

                //printf(" TOTAL number of neighbors =%d\n", graph->neighbors);
                neighbor = graph->nodes[id]->edges[neighbors]->dest;
                

                // search
                if (searchPQueue(queue[id], graph->nodes[neighbor]) == 1)
                {
                    insertPQueue(queue[id], graph->nodes[neighbor], graph->nodes[id]->edges[neighbors]->distance);
                }


                if (searchPQueue(queue[neighbor], graph->nodes[id]) == 1)
                {
                    insertPQueue(queue[neighbor], graph->nodes[id], graph->nodes[id]->edges[neighbors]->distance);
                }



                // neighbor of neighbor
                for (int i = 0; i < graph->neighbors; i++)
                {
                    neighbor_of_neighbor = graph->nodes[neighbor]->edges[i]->dest;
                    
                    if (id == neighbor_of_neighbor) continue;

                    distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_neighbor], graph->dim);
                    
                    // search
                    if (searchPQueue(queue[id], graph->nodes[neighbor_of_neighbor]) == 1)
                    {
                        insertPQueue(queue[id], graph->nodes[neighbor_of_neighbor], distance);
                    }


                    if (searchPQueue(queue[neighbor_of_neighbor], graph->nodes[id]) == 1)
                    {
                        insertPQueue(queue[neighbor_of_neighbor], graph->nodes[id], distance);
                    }
                }



                // reverse neighbor of neighbor
                for (int i = 0; i < graph->nodes[neighbor]->nreverse; i++)
                {
                    reverse_of_neighbor = graph->nodes[neighbor]->reverse[i]->src;

                    if (id == reverse_of_neighbor) continue;

                    distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_neighbor], graph->dim);
                    
                    // search
                    if (searchPQueue(queue[id], graph->nodes[reverse_of_neighbor]) == 1)
                    {
                        insertPQueue(queue[id], graph->nodes[reverse_of_neighbor], distance);
                    }


                    if (searchPQueue(queue[reverse_of_neighbor], graph->nodes[id]) == 1)
                    {
                        insertPQueue(queue[reverse_of_neighbor], graph->nodes[id], distance);
                    }
                }


            }



            // REVERSE NEIGHBORS
            for (int rev = 0; rev < graph->nodes[id]->nreverse; rev++)
            {
                // reverse neighbor
                reverse = graph->nodes[id]->reverse[rev]->src;
                
                // search
                if (searchPQueue(queue[id], graph->nodes[reverse]) == 1)
                {
                    insertPQueue(queue[id], graph->nodes[reverse], graph->nodes[id]->reverse[rev]->distance);
                }


                if (searchPQueue(queue[reverse], graph->nodes[id]) == 1)
                {
                    insertPQueue(queue[reverse], graph->nodes[id], graph->nodes[id]->reverse[rev]->distance);
                }



                // neighbors of reverse neighbor
                for (int i = 0; i < graph->neighbors; i++)
                {
                    neighbor_of_reverse = graph->nodes[reverse]->edges[i]->dest;

                    if (id == neighbor_of_reverse) continue;

                    distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_reverse], graph->dim);

                    // search
                    if (searchPQueue(queue[id], graph->nodes[neighbor_of_reverse]) == 1)
                    {
                        insertPQueue(queue[id], graph->nodes[neighbor_of_reverse], distance);
                    }


                    if (searchPQueue(queue[neighbor_of_reverse], graph->nodes[id]) == 1)
                    {
                        insertPQueue(queue[neighbor_of_reverse], graph->nodes[id], distance);
                    }
                    
                }



                // reverse neighbors of reverse neighbor
                for (int i = 0; i < graph->nodes[reverse]->nreverse; i++)
                {
                    reverse_of_reverse = graph->nodes[reverse]->reverse[i]->src;

                    if (id == reverse_of_reverse) continue;

                    distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_reverse], graph->dim);
                    
                    // search
                    if (searchPQueue(queue[id], graph->nodes[reverse_of_reverse]) == 1)
                    {
                        insertPQueue(queue[id], graph->nodes[reverse_of_reverse], distance);
                    }
                    

                    if (searchPQueue(queue[reverse_of_reverse], graph->nodes[id]) == 1)
                    {
                        insertPQueue(queue[reverse_of_reverse], graph->nodes[id], distance);
                    }
                }
            }
        }

        printf("\n\n\n");

        // INITIALISE REVERSE
        for (int id = 0; id < row; id++)
        {
            graph->nodes[id]->oldn = graph->nodes[id]->nreverse;
            graph->nodes[id]->nreverse = 0;
        }
        
        for (int id = 0; id < row; id++)
        {
            for (int i = 0; i < nedges; i++)
            {
                //printf("ID%d OLD DEST%d\n", id, graph->nodes[id]->edges[i]->dest);
            }
            
        }

        // UPDATE EDGES
        for (int id = 0; id < row; id++)
        {
            // get new edges
            for(int i = 0; i < nedges; i++)
            {
                new_edges[i] = extractMin(queue[id]);
                //new_edges[i] = &temp;
               // printf("EXTRACT MIN id%d => %d distance:%f\n", id, new_edges[i].node->id, new_edges[i].distance);
            }

            for(int i = 0; i < nedges; i++)
            {
                //printf("EXTRACT MIN id%d => %d distance:%f\n", id, new_edges[i].node->id, new_edges[i].distance);
            }
            printf("\n\n\n");

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
                        printf("..\n");
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
                    
                    if (searchPQueue(queue[id], new_edges[i].node) == 1)
                    {
                        graph->nodes[id]->edges[i]->src = graph->nodes[id]->id;
                        graph->nodes[id]->edges[i]->dest = new_edges[i].node->id;
                        graph->nodes[id]->edges[i]->distance = new_edges[i].distance;

                        dest = graph->nodes[id]->edges[i]->dest;    

                        //printf("%d nreverse:%d \n",dest, graph->nodes[dest]->nreverse);
                    
                        graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = graph->nodes[id]->edges[i];
                        graph->nodes[dest]->nreverse++;
                    }
                    
                }

                add = 0;

            }
            
            // if all nodes are the same, STOP ITERATIONS
            if (add == row)
            {
                flag = 1;
                break;
            }
        
        }
        

    } while (flag == 0);


    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < nedges; i++)
        {
            //printf("FINAL\nid %d => %d\n", graph->nodes[id]->id, graph->nodes[id]->edges[i]->dest);
        }
    }


    printf("wow so fast\n");
    // free queue

    //randomid = rand()%row;  // prob wrong
    flag = 1;

    start = malloc(graph->dim * sizeof(*start));
    
    
    
    // starting point for search
    for (int i = 0; i < graph->dim; i++)
    {
        start[i] = rand();
    }

    // search for the k-nearest neighbors of given point
    do
    {
    /* code */
    } while (flag == 0);
    
    
    return 0;
}