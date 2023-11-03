#include "graph.h"
#include "pqueue.h"

typedef struct pqueue* PQ;
int pqueue_insert(PQ queue, Node a, int distance);

int main(void)
{
    Graph graph;
    const char* filename = "data_structures/5k.txt";
    int nedges = 3;
    int row = 9759;
    int col = 3;
    int flag = 0;
    int randomid;
    int distance;
    int* point;
    int* start;
    PQ queue;
    int neighbor, neighbor_of_neighbor;
    int rneighbor;

    graph = createGraph(nedges, filename, row, col);
    point = malloc(graph->dim * sizeof(*point));
    srand(time(0));

    // random point for search
    for (int i = 0; i < graph->dim; i++)
    {
        point[i] = rand();
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
                neighbor = graph->nodes[id]->edges[neighbors]->dest; // correct
                pqueue_insert(queue, graph->nodes[neighbor], graph->nodes[id]->edges[neighbors]->distance);


                // neighbor of neighbor
                for (int non = 0; non < graph->neighbors; non++)
                {
                    neighbor_of_neighbor = graph->nodes[neighbor]->edges[non]->dest;
                    distance = compute_distance(graph->nodes[id], graph->nodes[neighbor_of_neighbor], graph->dim);
                    pqueue_insert(queue, graph->nodes[neighbor_of_neighbor], distance);
                }

                flag = 0;
            }

            // REVERSE NEIGHBORS
            for (int reverse = 0; reverse < graph->nodes[id]->nreverse; reverse++)
            {
                // reverse neighbor
                rneighbor = graph->nodes[id]->reverse[reverse]->src;
                pqueue_insert(queue, graph->nodes[rneighbor], graph->nodes[id]->reverse[reverse]->distance);

                // reverse neighbor of reverse neighbor
                for (int ror = 0; ror < graph->nodes[id]->nreverse; ror++)
                {

                }

                flag = 0;
            }
            
            //---------------------------------------//
            // UPDATE K-NEAREST NEIGHBORS OF NODE[ID]//
            //---------------------------------------//
        }

    } while (flag == 0);

    randomid = rand()%row;
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