#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct bankNode BankNode;
typedef struct bankNode *PtrBankNode;

typedef struct currFromNode CurrFromNode;
typedef struct currFromNode *PtrCurrFromNode;

typedef struct currToNode CurrToNode;
typedef struct currToNode *PtrCurrToNode;

struct bankNode
{
    char bankname[20];
    int currno;
    PtrBankNode next;
    PtrCurrFromNode Currhead;
};
/*
Conversion: FROM a currency TO a currency
*/
struct currFromNode
{
    char currname[20];
    PtrCurrFromNode next;
    PtrCurrToNode FirstCurrTo;
};

struct currToNode
{
    char currname[20];
    float currconv;
    PtrCurrToNode next;
};

PtrBankNode InitBankNode()
{
    PtrBankNode P = (PtrBankNode)malloc(sizeof(BankNode));
    P->currno = 0;
    P->Currhead = NULL;
    PtrCurrFromNode T = (PtrCurrFromNode)malloc(sizeof(CurrFromNode));
    T->FirstCurrTo = NULL;
    T->next = NULL;
    P->Currhead = T;
    P->next = NULL;
    return P;
}

PtrCurrFromNode InitCurrFromNode()
{
    PtrCurrFromNode P = (PtrCurrFromNode)malloc(sizeof(CurrFromNode));
    P->FirstCurrTo = NULL;
    P->next = NULL;
    return P;
}

PtrCurrToNode InitCurrToNode()
{
    PtrCurrToNode P = (PtrCurrToNode)malloc(sizeof(CurrToNode));
    P->currconv = 0;
    P->next = NULL;
    return P;
}

int main()
{
    PtrBankNode BankHead = InitBankNode();
    char command[20];
    printf("~ ");
    scanf("%s", command);
    while(strcmp(command, "exit") != 0)
    {
        if(strcmp(command, "addBank") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            PtrBankNode T = InitBankNode();
            strcpy(T->bankname, bankname);
            PtrBankNode X = BankHead;
            bool v = 1;
            while(X->next != NULL)
            {
                X = X->next;
                if(strcmp(X->bankname, bankname) == 0)
                {
                    printf("Error: Bank %s already exist\n", bankname);
                    v = 0;
                    break;
                }
            }
            if(v)
            {
                X->next = T;
                T->next = NULL;
                printf("Added bank %s\n", bankname);
            }
        }
        else if(strcmp(command, "printBank") == 0)
        {
            bool v = 1;
            PtrBankNode X = BankHead;
            if(X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            if(v)
            {
                X = X->next;
                while(X != NULL)
                {
                    printf("%s ", X->bankname);
                    X = X->next;
                }
                printf("\n");
            }
        }
        else if(strcmp(command, "delBank") == 0)
        {
            //check again for leaks
            char bankname[20];
            scanf("%s", bankname);
            PtrBankNode X = BankHead;
            PtrBankNode Y = X->next;
            bool v = 1;
            for(; Y != NULL; Y = Y->next, X = X->next)
            {
                if(strcmp(bankname, Y->bankname) == 0)
                {
                    X->next = Y->next;
                    v = 0;
                    break;
                }
            }
            if(v)
            {
                printf("Error: Bank %s does not exist\n", bankname);
            }
            if(!v)
            {
                PtrCurrFromNode A = Y->Currhead;
                while(A->next != NULL)
                {
                    A = A->next;
                    PtrCurrToNode S = A->FirstCurrTo;
                    while(S->next != NULL)
                    {
                        PtrCurrToNode T = S->next;
                        S->next = T->next;
                        free(T);
                    }
                }
                free(Y->Currhead);
                free(Y);
            }
            
        }

        else if(strcmp(command, "addCurr") == 0)
        {
            char currname[20];
            char bankname[20];
            scanf("%s %s", currname, bankname);
            bool v = 1;
            PtrBankNode X = BankHead;
            if(X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            else
            {
                X = X->next;
            }
            if(v)
            {
                while((strcmp(X->bankname, bankname) != 0) && X->next != NULL)
                {
                    X = X->next;
                }
                if(X->next == NULL && (strcmp(X->bankname, bankname) != 0))
                {
                    v = 0;
                    printf("Error: Bank %s does not exist\n", bankname);
                }
            }

            if(v)
            {
                (X->currno)++;
                PtrCurrFromNode P = X->Currhead;
                PtrCurrFromNode Q = P;
                if(P->next == NULL)
                {
                    PtrCurrFromNode T = InitCurrFromNode();
                    strcpy(T->currname, currname);
                    PtrCurrToNode temp = InitCurrToNode();
                    strcpy(temp->currname, currname);
                    T->FirstCurrTo = temp;
                    P->next = T;
                    printf("Added currency %s to bank %s\n", currname, bankname);
                }
                else
                {
                    bool t = 1;
                    while(P->next != NULL)
                    {
                        P = P->next;
                        if(strcmp(P->currname, currname) == 0)
                        {
                            t = 0;
                            printf("Error: Currency %s already exists in bank %s\n", currname, bankname);
                        }
                    }
                    if(t)
                    {
                        PtrCurrFromNode P = X->Currhead;
                        while(P->next != NULL)
                        {
                            P = P->next;
                            PtrCurrToNode L = P->FirstCurrTo;
                            while(L->next != NULL)
                            {
                                L = L->next;
                            }
                            PtrCurrToNode temp = InitCurrToNode();
                            strcpy(temp->currname, currname);
                            L->next = temp;
                        }
                        PtrCurrFromNode temp2 = InitCurrFromNode();
                        strcpy(temp2->currname, currname);
                        P->next = temp2;

                        Q = Q->next;
                        PtrCurrToNode trv = InitCurrToNode();
                        strcpy(trv->currname, Q->currname);
                        temp2->FirstCurrTo = trv;

                        while(Q->next != NULL)
                        {
                            Q = Q->next;
                            PtrCurrToNode temp = InitCurrToNode();
                            strcpy(temp->currname, Q->currname);
                            trv->next = temp;
                            trv = trv->next;
                        }
                        printf("Added currency %s to bank %s\n", currname, bankname);
                    }
                }
            }
        }
        else if(strcmp(command, "printAllCurr") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            PtrBankNode X = BankHead;
            bool v = 1;
            if(X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            else
            {
                X = X->next;
            }
            while((strcmp(X->bankname, bankname) != 0) && X->next != NULL)
            {
                X = X->next;
            }

            if(v)
            {
                if (X->next == NULL && (strcmp(X->bankname, bankname) != 0))
                {
                    v = 0;
                    printf("Error: Bank %s does not exist\n", bankname);
                }
            }

            if(v)
            {
                if (X->currno == 0)
                {
                    printf("Error: No currencies exist in bank %s\n", bankname);
                    v = 0;
                }
            }

            if(v)
            {
                PtrCurrFromNode P = X->Currhead;
                printf("\t");
                while (P->next != NULL)
                {
                    P = P->next;
                    PtrCurrToNode Q = P->FirstCurrTo;
                    printf("%s\t\t", P->currname);
                }
                printf("\n");
                P = X->Currhead;
                while (P->next != NULL)
                {
                    P = P->next;
                    PtrCurrToNode Q = P->FirstCurrTo;
                    printf("%s\t", P->currname);
                    while (Q != NULL)
                    {
                        printf("%.2f\t\t", Q->currconv);
                        Q = Q->next;
                    }
                    printf("\n");
                }
            }
        }
        else if (strcmp(command, "delCurr") == 0)
        {
            char currname[10];
            char bankname[10];
            scanf("%s %s", currname, bankname);
            PtrBankNode X = BankHead;
            bool v = 1;
            if (X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            else
            {
                X = X->next;
            }

            while ((strcmp(X->bankname, bankname) != 0) && X->next != NULL)
            {
                X = X->next;
            }

            if (v)
            {
                if (X->next == NULL && (strcmp(X->bankname, bankname) != 0))
                {
                    v = 0;
                    printf("Error: Bank %s does not exist\n", bankname);
                }
            }

            if (v)
            {
                (X->currno)--;
                bool t = 0;
                PtrCurrFromNode P = X->Currhead;
                PtrCurrFromNode R;
                PtrCurrFromNode temp;
                while(P->next != NULL)
                {
                    R = P;
                    P = P->next;
                    if (strcmp(P->currname, currname) == 0)
                    {
                        temp = P;
                        t = 1;
                        break;
                    }
                }
                if(!t)
                {
                    printf("Error: Currency %s does not exist in bank %s\n", currname, bankname);
                }
                if (t)
                {
                    if(temp == X->Currhead->next)
                    {
                        PtrCurrFromNode K = temp;
                        while(K->next != NULL)
                        {
                            K = K->next;
                            PtrCurrToNode M = K->FirstCurrTo;
                            K->FirstCurrTo = M->next;
                            free(M);
                        }
                        PtrCurrToNode S = temp->FirstCurrTo;
                        while(S->next != NULL)
                        {
                            PtrCurrToNode T = S->next;
                            S->next = T->next;
                            free(T);
                            
                        }
                        X->Currhead->next = temp->next;
                        free(temp);
                    }
                    else
                    {
                        P = X->Currhead;
                        while (P->next != NULL)
                        {
                            P = P->next;
                            PtrCurrToNode L = P->FirstCurrTo;
                            PtrCurrToNode M = L;
                            while(strcmp(L->currname,currname) != 0)
                            {
                                M = L;
                                L = L->next;
                            }
                            M->next = L->next;
                            free(L);
                        }
                        PtrCurrToNode S = temp->FirstCurrTo;
                        R->next = temp->next;
                        while(S->next != NULL)
                        {
                            PtrCurrToNode T = S->next;
                            S->next = T->next;
                            free(T);
                        }
                        free(temp);
                    }
                    
                    
                }
            }
        }
        else if (strcmp(command, "addConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            float currconv;
            scanf("%s %s %f %s", currfrom,currto,&currconv,bankname);
            PtrBankNode X = BankHead;
            bool v = 1;
            if (X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            else
            {
                X = X->next;
            }

            while ((strcmp(X->bankname, bankname) != 0) && X->next != NULL)
            {
                X = X->next;
            }

            if (v)
            {
                if (X->next == NULL && (strcmp(X->bankname, bankname) != 0))
                {
                    v = 0;
                    printf("Error: Bank %s does not exist\n", bankname);
                }
            }
            if (v)
            {
                bool t = 0;
                PtrCurrFromNode P = X->Currhead;
                while(P->next != NULL)
                {
                    P = P->next;
                    if (strcmp(P->currname, currfrom) == 0)
                    {
                        t = 1;
                        break;
                    }
                }
                if(!t)
                {
                    printf("Error: Currency %s does not exist in bank %s\n", currfrom, bankname);
                }

                bool u = 0;
                P = X->Currhead;
                while(P->next != NULL)
                {
                    P = P->next;
                    if (strcmp(P->currname, currto) == 0)
                    {
                        u = 1;
                        break;
                    }
                }
                if(!u)
                {
                    printf("Error: Currency %s does not exist in bank %s\n", currto, bankname);
                }
                if(u && t)
                {
                    if(strcmp(currto,currfrom) == 0)
                    {
                        printf("Error: Conversion between same currency not possible\n");
                    }
                    else
                    {
                        PtrCurrFromNode P = X->Currhead;
                        while(P->next != NULL)
                        {
                            P = P->next;
                            if (strcmp(P->currname, currfrom) == 0)
                            {
                                break;
                            }
                        }
                        PtrCurrToNode Q = P->FirstCurrTo;
                        while(strcmp(Q->currname,currto) != 0)
                        {
                            Q = Q->next;
                        }
                        bool q = 1;
                        if(Q->currconv != 0)
                        {
                            q = 0;
                            printf("Error: Conversion for %s to %s already given\n",currfrom,currto);
                        }
                        else
                        {
                            Q->currconv = currconv;
                        }
                        
                        if(q)
                        {
                            P = X->Currhead;
                            while(P->next != NULL)
                            {
                                P = P->next;
                                if (strcmp(P->currname, currto) == 0)
                                {
                                    break;
                                }
                            }
                            Q = P->FirstCurrTo;
                            while(strcmp(Q->currname,currfrom) != 0)
                            {
                                Q = Q->next;
                            }
                            //Q->currconv = 1/currconv;
                            Q->currconv = currconv;
                        }
                        
                    }
                }

            }
        }
        else if (strcmp(command, "delConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            
            scanf("%s %s %s", currfrom,currto,bankname);
            PtrBankNode X = BankHead;
            bool v = 1;
            if (X->next == NULL)
            {
                printf("No banks exist\n");
                v = 0;
            }
            else
            {
                X = X->next;
            }

            while ((strcmp(X->bankname, bankname) != 0) && X->next != NULL)
            {
                X = X->next;
            }

            if (v)
            {
                if (X->next == NULL && (strcmp(X->bankname, bankname) != 0))
                {
                    v = 0;
                    printf("Error: Bank %s does not exist\n", bankname);
                }
            }
            if (v)
            {
                bool t = 0;
                PtrCurrFromNode P = X->Currhead;
                while(P->next != NULL)
                {
                    P = P->next;
                    if (strcmp(P->currname, currfrom) == 0)
                    {
                        t = 1;
                        break;
                    }
                }
                if(!t)
                {
                    printf("Error: Currency %s does not exist in bank %s\n", currfrom, bankname);
                }

                bool u = 0;
                P = X->Currhead;
                while(P->next != NULL)
                {
                    P = P->next;
                    if (strcmp(P->currname, currto) == 0)
                    {
                        u = 1;
                        break;
                    }
                }
                if(!u)
                {
                    printf("Error: Currency %s does not exist in bank %s\n", currto, bankname);
                }
                if(u && t)
                {
                    if(strcmp(currto,currfrom) == 0)
                    {
                        printf("Error: Conversion between same currency not possible\n");
                    }
                    else
                    {
                        PtrCurrFromNode P = X->Currhead;
                        while(P->next != NULL)
                        {
                            P = P->next;
                            if (strcmp(P->currname, currfrom) == 0)
                            {
                                break;
                            }
                        }
                        PtrCurrToNode Q = P->FirstCurrTo;
                        while(strcmp(Q->currname,currto) != 0)
                        {
                            Q = Q->next;
                        }
                        Q->currconv = 0;
                        
                        P = X->Currhead;
                        while(P->next != NULL)
                        {
                            P = P->next;
                            if (strcmp(P->currname, currto) == 0)
                            {
                                break;
                            }
                        }
                        Q = P->FirstCurrTo;
                        while(strcmp(Q->currname,currfrom) != 0)
                        {
                            Q = Q->next;
                        }
                        Q->currconv = 0;
                        
                        
                    }
                }

            }


        }
        else if (strcmp(command, "getArray") == 0)
        {
            //copies all the currconv into a link list a[X->currno][X->currno]
        }
        else if (strcmp(command, "commands") == 0)
        {
            //list of commands and their arguments in order
        }
        else
        {
            printf("Syntax Error\n");
        }
        printf("~ ");
        scanf("%s", command);
    }
}
// adding a pointer at end of link list

struct PQueueNode   //minheap nodes
{
    int  n;//Vertex no. or index of vertex
    int dist;// will store the current distance value of vertex
};

struct PQueue
{
    int size;   // No. of heapnodes in Pqueue present,capacity  will remain same but size will decrease when minnodes will be extracted 
    int capacity; // No. of vertices in this particular graph
    int *position; // To keep track of the position of vertex in minheap,can directly access that vertex in minheap  as its position is stored here
    struct PQueueNode **node; //Will point to PqueueNode or minheap nodes
};

struct PQueueNode* newPNode(int n,int dist)  // to create a PQueue node
{
    struct PQueueNode* PNode =(struct PQueueNode*)malloc(sizeof(struct PQueueNode));
    PNode->n = n;
    PNode->dist = dist;
    return PNode;
}
 
struct PQueue* createPQueue(int capacity)   // To create a priority queue of capacity equal to no. of vertices
{
    struct PQueue* pQueue =(struct PQueue*)malloc(sizeof(struct PQueue));
    pQueue->position = (int *)malloc(capacity * sizeof(int));  // position array's size would be no. of vertices as it keeps track of position of vertices in pqueue
    pQueue->size = 0;  //initially size is 0 as no minheap node is created
    pQueue->capacity = capacity;  //capacity is fixed,always equal to no. of vertices
    pQueue->node =(struct PQueueNode**)malloc(capacity *sizeof(struct PQueueNode*));
    return pQueue;
}
 
void swapMinHeapNode(struct PQueueNode** a,struct PQueueNode** b)  //swap 2 pqueue nodes,would be required as during heapify swapping is must
{
    struct PQueueNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct PQueue* pQueue,int index) // heapify process is there to make PQueue follow the minheap condition
{                                                // that every node is smaller than its children
    int smallest, left, right;                   // Here in this function we will also swap nodes and change their position in  position array
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
 
    if (left < pQueue->size && pQueue->node[left]->dist < pQueue->node[smallest]->dist )
      smallest = left;
 
    if (right < pQueue->size && pQueue->node[right]->dist < pQueue->node[smallest]->dist )
      smallest = right;
 
    if (smallest != index)
    {
        PQueueNode *smallestNode = pQueue->node[smallest];  // Nodes which are neded to be swapped in minheap
        PQueueNode *idxNode = pQueue->node[index];          // so that condition of minheap is followed
  
        pQueue->position[smallestNode->n] = index;          // here positions of nodes are changed
        pQueue->position[idxNode->n] = smallest;            // which would be swapped 
 
        swapMinHeapNode(&pQueue->node[smallest],&pQueue->node[index]);  // the nodes are swapped here 
 
        minHeapify(pQueue, smallest);  //need to recursively call this function to convert entire tree in minheap
    }
}
 
int isEmpty(struct PQueue* pQueue)  //to check if PQueue is empty or not
{
    return pQueue->size == 0;   // if size is 0 that means there are no minheap nodes in our priority queue.
}
 
struct PQueueNode* extractMin(struct PQueue*pQueue)  // to extarct minimum node from pqueue which would be first node
{
    if (isEmpty(pQueue))return NULL;
 
    struct PQueueNode* root =pQueue->node[0]; // store the first node in root node and do operations on it
 
    struct PQueueNode* lastNode =pQueue->node[pQueue->size - 1];  //here root node is replaced with last node
    pQueue->node[0] = lastNode;
 
    pQueue->position[root->n] = pQueue->size-1;  // positions are updated in array for above replacement
    pQueue->position[lastNode->n] = 0;
 
    --pQueue->size;   // size is decreased by one as one node is extracted,capacity or size of array will remain same
    minHeapify(pQueue, 0);  // heapify the root to make sure minheap condition is followed
 
    return root;
}
 
void decreaseKey(struct PQueue* pQueue,int n, int dist)  // function to update the distance value(decrease distance particullarly) in heap nodes
{
    int i = pQueue->position[n];  // here position array is used to get the position of particular vertex in minheap directly

    pQueue->node[i]->dist = dist;  // get to node with the help if i found above and update its distance value

    while (i && pQueue->node[i]->dist <pQueue->node[(i - 1) / 2]->dist)  //travel up the tree while checking with parent that whether minheap condition is followed or not
    {
        pQueue->position[pQueue->node[i]->n] =(i-1)/2;  // if minheap condition is not followed you will enter in loop
        pQueue->position[pQueue->node[(i-1)/2]->n] = i;  // and keep on swapping node with parent untill minheap condition is not followed,swap position in position array also
        swapMinHeapNode(&pQueue->node[i],&pQueue->node[(i - 1) / 2]);
 
        i = (i - 1) / 2; ///go to next parent
    }
}
bool IsInPqueue(struct PQueue *pQueue, int n) // to check whether vertex n is priority queue or not
{
   if (pQueue->position[n] < pQueue->size)  // if it is not there then it would be outside the current size of priority queue
     return true;
   return false;
}
