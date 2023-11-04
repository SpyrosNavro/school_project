#include "header_files/graph.h"
#include "header_files/pqueue.h"

typedef struct PQueue* PQ;

int main(void)
{
    Graph graph;
    const char* filename = "data_structures/5k.txt";
    int nedges = 3;
    int row = 9759;
    int col = 3;
    int flag = 0;
//    int randomid;
    float distance;
    int* point;
    int* start;
    PQ queue[row];
    int neighbor, neighbor_of_neighbor, neighbor_of_reverse;
    int reverse, reverse_of_neighbor, reverse_of_reverse;

    graph = createGraph(nedges, filename, row, col);
    point = malloc(graph->dim * sizeof(*point));
    srand(time(0));

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

    do
    {
        flag = 1;
        
        for (int id = 0; id < row; id++)
        {


            // NEIGHBORS
            for (int neighbors = 0; neighbors < graph->neighbors; neighbors++)
            {
                // neighbor
                neighbor = graph->nodes[id]->edges[neighbors]->dest;
                insertPQueue(queue[id], graph->nodes[neighbor], graph->nodes[id]->edges[neighbors]->distance);
                insertPQueue(queue[neighbor], graph->nodes[id], graph->nodes[id]->edges[neighbors]->distance);

                // neighbor of neighbor
                for (int i = 0; i < graph->neighbors; i++)
                {
                    neighbor_of_neighbor = graph->nodes[neighbor]->edges[i]->dest;
                    distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_neighbor], graph->dim);
                    insertPQueue(queue[id], graph->nodes[neighbor_of_neighbor], distance);
                    insertPQueue(queue[neighbor_of_neighbor], graph->nodes[id], distance);
                }


                // reverse neighbor of neighbor
                for (int i = 0; i < graph->nodes[neighbor]->nreverse; i++)
                {
                    reverse_of_neighbor = graph->nodes[neighbor]->reverse[i]->src;
                    distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_neighbor], graph->dim);
                    insertPQueue(queue[id], graph->nodes[reverse_of_neighbor], distance);
                    insertPQueue(queue[reverse_of_neighbor], graph->nodes[id], distance);
                }


            }



            // REVERSE NEIGHBORS
            for (int rev = 0; rev < graph->nodes[id]->nreverse; rev++)
            {
                // reverse neighbor
                reverse = graph->nodes[id]->reverse[rev]->src;
                insertPQueue(queue[id], graph->nodes[reverse], graph->nodes[id]->reverse[rev]->distance);
                insertPQueue(queue[reverse], graph->nodes[id], graph->nodes[id]->reverse[rev]->distance);


                // neighbors of reverse neighbor
                for (int i = 0; i < graph->neighbors; i++)
                {
                    neighbor_of_reverse = graph->nodes[reverse]->edges[i]->dest;
                    distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_reverse], graph->dim);
                    insertPQueue(queue[id], graph->nodes[neighbor_of_reverse], distance);
                    insertPQueue(queue[neighbor_of_reverse], graph->nodes[id], distance);
                }


                // reverse neighbors of reverse neighbor
                for (int i = 0; i < graph->nodes[reverse]->nreverse; i++)
                {
                    reverse_of_reverse = graph->nodes[reverse]->reverse[i]->src;
                    distance = compute_distance(graph->nodes[id], graph->nodes[reverse_of_reverse], graph->dim);
                    insertPQueue(queue[id], graph->nodes[reverse_of_reverse], distance);
                    insertPQueue(queue[reverse_of_reverse], graph->nodes[id], distance);
                }


            }
            
            //---------------------------------------//
            // UPDATE K-NEAREST NEIGHBORS OF NODE[ID]//
            //---------------------------------------//
        }

    } while (flag == 0);

//    randomid = rand()%row;
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
