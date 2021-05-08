#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max 9999 //infinity
//use priority queue func from shubhs code and the graph and user-interface from preraks
//pseudo code for dijkstra 
//using priority queue
//will be combined and complied later
int dijkstra(bank *g, int source, int dest)
{
    int vertex = g->vertexno;
    int v = vertex;
    int distance[v + 1]; // distance array;
    //calling priority queue to make the algo more efficient
    PQueue *pq = createminheap(v);

    for (int i = 0; i <= v; i++)
    {

        distance[i] = max;
        pq->node[i] = neiwPNode(i, distance[i]);
        pq->pos[i] = i;
    }
    distance[source] = 0;
    pq->pos[source] = source;
    pq->size = v;
    decreaseKey(pq, source, distance[source]);
    while (!isEmpty(pq))
    {
        PQueueNode *pqnode;
        pqnode = extract(pq);
        int x;
        x = pqnode->v;
        List *update;
        update = g->list[x].head;
        while (update != NULL)
        {
            int y;
            y = update->num;
            if (isInpq(pq, y) && distance[x] != max && update->weight + distance[x] < distance[y])
            {
                distance[y] = distance[x] + update->weight;
                decreaseKey(pq, y, distance[y]);
            }
            update = update->next;
        }
    }
    return distance[dest];
}
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;
    // n = no of banks;
    p = ptrtobank;
    int ans[n] for (int i = 1; i < n + 1; i++)
    {

        int ans[i] = dijkstra(p, source, dest);
        //if ans[i] == 9999 no path exists
        printf("%s  %d", p->bankname, ans[i]);
        //
        p = p->next;
    }
    qsort(ans, n, sizeof(int), cmpfunc);
    // best asnwer is  ans[0];

    return 0;
}