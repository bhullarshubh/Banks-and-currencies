#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node
{
    int vertex;
    struct node *next;
};
typedef struct node node;
struct graph
{
    int v;
    struct node **list;
    int *visited;
};
typedef struct graph graph;

graph* creategraph(int v)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->list = malloc(v * sizeof(node *));
    g->visited = (int *)malloc(v * sizeof(int));
    g->v = v;
    for (int i = 0; i < v; i++)
    {
        g->list[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}
node *createnode(int v)
{
    node *n = (node *)malloc(sizeof(struct node));
    n->vertex = v;
    n->next = NULL;
    return n;
}
void addedge(graph *g, int s, int d)
{
    node *new = createnode(d);
    new->next = g->list[s];
    g->list[s] = new;
}
/* void push(x)
{
  top++;
  stack[top] = x;
} */
void dfs(graph *g, int vertex1)
{
    node *a = g->list[vertex1];
    node *temp;
    temp = a;
    g->visited[vertex1] = 1;
    printf("%d -> ", vertex1);
    while (temp != NULL)
    {
        int nextvertex = temp-> vertex;
        if (g->visited[nextvertex] == 0)
        {
            dfs(g, nextvertex);
        }
        temp = temp->next;
    }
}
void print(graph* g)
{
    for (int i = 0; i < g -> v; i++)
    {
        node* temp = g -> list[i];
        printf("%d ",i);
        while (temp)
        {
            printf("%d -> ",temp -> vertex);
            temp = temp -> next;
        }
        printf("\n");
    }
    
}
int main()
{
    graph *g;
    int v;
    v = 6;
    g = creategraph(v);
    addedge(g, 5, 2);
    addedge(g, 5, 0);
    addedge(g, 4, 0);
    addedge(g, 4, 1);
    addedge(g, 2, 3);
    addedge(g, 3, 1);
    print(g);
    dfs(g, 5);
    printf("\n");
}