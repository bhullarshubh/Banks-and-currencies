#include "currency2.h"

PtrBankNode InitBankNode() //initializes a BankNode
{
    PtrBankNode P = (PtrBankNode)malloc(sizeof(BankNode));
    P->currno = 0;
    P->Currhead = NULL;
    PtrCurrFromNode Temp = InitCurrFromNode(); //initializes the Currhead node in the bank that the user is adding
    P->Currhead = Temp;
    P->next = NULL;
    return P;
}

PtrCurrFromNode InitCurrFromNode() //initializes a CurrFromNode
{
    PtrCurrFromNode P = (PtrCurrFromNode)malloc(sizeof(CurrFromNode));
    P->FirstCurrTo = NULL;
    P->next = NULL;
    return P;
}

PtrCurrToNode InitCurrToNode() //initializes a CurrToNode
{
    PtrCurrToNode P = (PtrCurrToNode)malloc(sizeof(CurrToNode));
    P->currconv = 0;
    P->next = NULL;
    return P;
}

PtrListNode InitListNode() //initializes a ListNode
{
    PtrListNode P = (PtrListNode)malloc(sizeof(ListNode));
    P->index = 0;
    P->currconv = 0;
    P->next = 0;
    return P;
}

PtrBankNode findBank(PtrBankNode BankHead, char bankname[]) //given the name of the bank we want to find as an argument, this function returns a pointer to the BankNode with that name
{
    PtrBankNode BankTrv = BankHead;
    while ((strcmp(BankTrv->bankname, bankname) != 0) && BankTrv->next != NULL)
    {
        BankTrv = BankTrv->next;
    }
    return BankTrv;
}

PtrCurrFromNode findCurrFromNode(PtrCurrFromNode TrvCurrFrom, char currname[]) //given the name of the currency the user wants to find as argument, this function returns a pointer to the CurrFromNode with that name
{
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        if (strcmp(TrvCurrFrom->currname, currname) == 0)
        {
            return TrvCurrFrom;
        }
    }
}

PtrCurrToNode findCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]) // given the name of the currency the user wants to find as argument, this function returns a pointer to the CurrToNode with that name
{
    PtrCurrToNode TrvCurrTo = TrvCurrFrom->FirstCurrTo;
    while (strcmp(TrvCurrTo->currname, currname) != 0)
    {
        TrvCurrTo = TrvCurrTo->next;
    }
    return TrvCurrTo;
}

PtrCurrFromNode addCurrFromNode(PtrCurrFromNode CurrHead, char currname[]) // Adds a CurrFromNode at the end of the link list of CurrFromNodes, with its name as the string passed as an argument
{
    while (CurrHead->next != NULL)
    {
        CurrHead = CurrHead->next;
    }
    PtrCurrFromNode Temp = InitCurrFromNode();
    strcpy(Temp->currname, currname);
    CurrHead->next = Temp;
    return Temp;
}

PtrPQueueNode newPNode(int n, int dist) // to create a PQueue node
{
    PtrPQueueNode PNode = (PtrPQueueNode)malloc(sizeof(PQueueNode));
    PNode->n = n;
    PNode->dist = dist;
    return PNode;
}

PtrPQueue createPQueue(int capacity) // To create a priority queue of capacity equal to no. of vertices
{
    PtrPQueue pQueue = (PtrPQueue)malloc(sizeof(struct PQueue));
    pQueue->position = (int *)malloc(capacity * sizeof(int)); // position array's size would be no. of vertices as it keeps track of position of vertices in pqueue
    pQueue->size = 0;                                         //initially size is 0 as no minheap node is created
    pQueue->capacity = capacity;                              //capacity is fixed,always equal to no. of vertices
    pQueue->node = (PtrPtrPQueueNode)malloc(capacity * sizeof(PtrPQueueNode));
    return pQueue;
}

PtrPQueueNode extractMin(PtrPQueue pQueue) // to extarct minimum node from pqueue which would be first node
{
    if (isEmpty(pQueue))
        return NULL;

    PtrPQueueNode root = pQueue->node[0]; // store the first node in root node and do operations on it

    PtrPQueueNode lastNode = pQueue->node[pQueue->size - 1]; //here root node is replaced with last node
    pQueue->node[0] = lastNode;

    pQueue->position[root->n] = pQueue->size - 1; // positions are updated in array for above replacement
    pQueue->position[lastNode->n] = 0;

    --pQueue->size;        // size is decreased by one as one node is extracted,capacity or size of array will remain same
    minHeapify(pQueue, 0); // heapify the root to make sure minheap condition is followed

    return root;
}

// ALL BOOL FUNCTIONS HAVE A MODE PARAMETER, where if the mode if 1, the functions prints the error message, or else it doesn't print anything

bool BankDoesntExist(PtrBankNode BankHead, char bankname[], int mode) //to check if a bank with the given name exists in the link list of BankNodes
{
    PtrBankNode BankTrv = BankHead;
    while (BankTrv->next != NULL) //moves through link list of BankNodes and performs strcmps to check whether the name of the BankNode matches with the string bankname passed as argument
    {
        BankTrv = BankTrv->next;
        if (strcmp(BankTrv->bankname, bankname) == 0)
        {
            return 0;
        }
    }

    if (mode == 1)
    {
        printf("\nBank %s does not exist\n\n", bankname);
    }
    return 1;
}

bool NoBanksExist(PtrBankNode BankHead, int mode) //returns 0 if no banks exist, else returns 1
{
    PtrBankNode BankTrv = BankHead;
    if (BankTrv->next == NULL)
    {
        if (mode == 1)
        {
            printf("\nNo banks exist\n\n");
        }
        return 1;
    }
    return 0;
}

bool CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[], int mode) //takes a string as argument and returns 1 if a CurrFromNode has same name as that string, else returns 0
{
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        if (strcmp(TrvCurrFrom->currname, currname) == 0)
        {
            if (mode == 1)
            {
                printf("\nError: Currency %s already exist\n\n", currname);
            }
            return 1;
        }
    }
    return 0;
}

bool NoCurrencyExists(PtrBankNode BankHead, char bankname[], int mode) //returns 1 if no currencies have been added to a bank, else returns 0
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    if (BankTrv->currno == 0)
    {
        if (mode == 1)
        {
            printf("\nError: No currencies exists in bank %s\n\n", bankname);
        }
        return 1;
    }
    return 0;
}

bool IsInPqueue(PtrPQueue PQueue, int n) // to check whether vertex n is priority queue or not
{
    if (PQueue->position[n] < PQueue->size) // if it is not there then it would be outside the current size of priority queue
    {
        return true;
    }
    return false;
}

void addBank(PtrBankNode BankHead, char bankname[]) //adds a BankNode to the link list of BankNodes
{
    PtrBankNode BankTrv = findBank(BankHead, " ");
    PtrBankNode Temp = InitBankNode();
    strcpy(Temp->bankname, bankname);
    BankTrv->next = Temp;
    Temp->next = NULL;
    printf("\nAdded bank %s\n\n", bankname);
}

void printBanks(PtrBankNode BankHead) //prints list of BankNodes
{
    printf("\n");
    PtrBankNode BankTrv = BankHead->next;
    while (BankTrv != NULL)
    {
        printf("%s", BankTrv->bankname);
        if (BankTrv->next != NULL) // to prevent function from printing a comma after the last bank name has been printed
        {
            printf(", ");
        }
        BankTrv = BankTrv->next;
    }
    printf("\n\n");
}

void addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]) // adding a CurrToNode at the end of list of CurrToNodes
{
    if (TrvCurrFrom->FirstCurrTo == NULL) // case where the pointer to the CurrFromNode that is given as argument has no CurrToNodes linked to it
    {
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrFrom->FirstCurrTo = temp;
    }
    else
    {
        PtrCurrToNode TrvCurrTo = TrvCurrFrom->FirstCurrTo;
        while (TrvCurrTo->next != NULL)
        {
            TrvCurrTo = TrvCurrTo->next;
        }
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrTo->next = temp;
    }
}

void addCurr(PtrBankNode BankHead, char bankname[], char currname[]) // adds a CurrFromNode to a bank
{
    PtrBankNode BankTrv = findBank(BankHead, bankname); // stores the pointer to the bank in which we need to add the currency
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;    // Traversal pointer which moves through the link list of CurrFromNodes
    if (!CurrencyAlreadyPresent(TrvCurrFrom, currname, 1))
    {
        PtrCurrFromNode NewCurr = addCurrFromNode(BankTrv->Currhead, currname); //adds a CurrFromNode at the end of link list of CurrFromNodes
        while (TrvCurrFrom->next != NewCurr)
        {
            TrvCurrFrom = TrvCurrFrom->next;
            addCurrToNode(TrvCurrFrom, currname);          //adding a CurrToNode at the end of every link list of CurrFromNodes where TrvCurrFrom is pointing to the head pointer of these lists
            addCurrToNode(NewCurr, TrvCurrFrom->currname); //adds a CurrToNode at the end of link list of CurrToNodes with NewCurr being the head pointer
        }
        addCurrToNode(NewCurr, currname);
        (BankTrv->currno)++;
        printf("\nAdded currency %s to bank %s\n\n", currname, bankname);
    }
}

void printAllCurr(PtrBankNode BankHead, char bankname[]) //prints the adjacency matrix for a given bank
{
    printf("\n\n");
    PtrBankNode BankTrv = findBank(BankHead, bankname);

    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    printf("\t\t");
    //Together these two while loops print the adjacency matrix
    while (TrvCurrFrom->next != NULL) //while loop to print the heading of each column
    {
        TrvCurrFrom = TrvCurrFrom->next;
        printf("%s\t\t", TrvCurrFrom->currname);
    }

    printf("\n\n");
    TrvCurrFrom = BankTrv->Currhead;
    while (TrvCurrFrom->next != NULL) //prints heading of each row and currconv stored in each CurrToNode
    {
        TrvCurrFrom = TrvCurrFrom->next;
        PtrCurrToNode TrailCurrFrom = TrvCurrFrom->FirstCurrTo;
        printf("%s\t\t", TrvCurrFrom->currname);
        while (TrailCurrFrom != NULL)
        {
            printf("%.2f\t\t", TrailCurrFrom->currconv);
            TrailCurrFrom = TrailCurrFrom->next;
        }
        printf("\n\n\n");
    }
}

void delCurr(PtrBankNode BankHead, char currname[], char bankname[], int mode) //deletes a currency from the adjacency matrix of a bank
{
    // To delete a currency from the adjaceny matrix, we need to delete the link list of CurrToNodes which has its head pointer's name as the name of the currency the user wants to delete
    // Then it deletes a node from every other link list of CurrToNodes that has its currname as the string passed as argument
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    if (!CurrencyAlreadyPresent(TrvCurrFrom, currname, 0)) //if the no currency name in the bank matches with the string given as input, the function prints an error
    {
        if (mode == 1)
        {
            printf("\nError: Currency %s does not exist in bank %s\n\n", currname, bankname);
        }
    }
    else
    {
        PtrCurrFromNode Temp2 = findCurrFromNode(TrvCurrFrom, currname); //Temp2 stores the head pointer of the link list that needs to be deleted
        PtrCurrFromNode Temp = BankTrv->Currhead;
        while (Temp->next != Temp2) // Temp will point to the CurrFromNode right before Temp2
        {
            Temp = Temp->next;
        }
        (BankTrv->currno)--;

        if (Temp2 == BankTrv->Currhead->next) //if Temp2 is pointing to the first currency in the adjacency matrix (top left corner case)
        {
            PtrCurrFromNode TrvTemp = Temp2;
            while (TrvTemp->next != NULL) //deleting the first CurrToNode of every link list of CurrToNode
            {
                TrvTemp = TrvTemp->next;
                PtrCurrToNode TrvRowTemp = TrvTemp->FirstCurrTo;
                TrvTemp->FirstCurrTo = TrvRowTemp->next;
                free(TrvRowTemp);
            }
            PtrCurrToNode RowTemp = Temp2->FirstCurrTo; // pointing to the first CurrToNode of the list of CurrToNodes that needs to be completely deleted
            while (RowTemp->next != NULL)               //deleting entire list of CurrToNodes
            {
                PtrCurrToNode Temp3 = RowTemp->next;
                RowTemp->next = Temp3->next;
                free(Temp3);
            }
            BankTrv->Currhead->next = Temp2->next;
            free(Temp2); //deleting CurrFromNode from link list of CurrFromNodes
            printf("\nDeleted currency %s from bank %s\n\n", currname, bankname);
        }
        else
        {
            TrvCurrFrom = BankTrv->Currhead;
            while (TrvCurrFrom->next != NULL)
            {
                TrvCurrFrom = TrvCurrFrom->next;
                PtrCurrToNode RowTemp = TrvCurrFrom->FirstCurrTo;
                PtrCurrToNode TrailRowTemp = RowTemp;
                while (strcmp(RowTemp->currname, currname) != 0) //finding and deleting CurrToNodes that have same currname as the currency that needs to be deleted
                {
                    TrailRowTemp = RowTemp;
                    RowTemp = RowTemp->next;
                }
                TrailRowTemp->next = RowTemp->next;
                free(RowTemp);
            }
            PtrCurrToNode S = Temp2->FirstCurrTo;
            Temp->next = Temp2->next;
            while (S->next != NULL) //deleting entire list of CurrToNodes
            {
                PtrCurrToNode Temp4 = S->next;
                S->next = Temp4->next;
                free(Temp4);
            }
            free(Temp2); //deleting CurrFromNode from link list of CurrFromNodes
            printf("\nDeleted currency %s from bank %s\n\n", currname, bankname);
        }
    }
}

void findLoc(PtrCurrFromNode P, char currfrom[], char currto[], float currconv) //adds conversion rate at specified location in the adjacency matrix
{
    P = findCurrFromNode(P, currfrom);
    PtrCurrToNode Q = findCurrToNode(P, currto);
    Q->currconv = currconv;
}

void addConv(PtrBankNode BankHead, char currfrom[], char currto[], float currconv, char bankname[], int mode) //checks for errors and if none then calls findLoc and adds conversion rate to adjacency matrix
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    if (CurrencyAlreadyPresent(BankTrv->Currhead, currfrom, 0))
    {
        if (CurrencyAlreadyPresent(BankTrv->Currhead, currto, 0))
        {
            if (strcmp(currto, currfrom) == 0)
            {
                printf("\nError: Conversion between same currency not possible\n\n");
            }
            else
            {
                PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
                findLoc(TrvCurrFrom, currfrom, currto, currconv);
                if (mode == 1)
                {
                    printf("\nAdded conversion %s to %s to bank %s\n\n", currfrom, currto, bankname);
                }
                else
                {
                    printf("\nDeleted conversion %s to %s in bank %s\n\n", currto, currfrom, bankname);
                }
            }
        }
        else
        {
            printf("\nError: Currency %s does not exist in %s\n\n", currto, bankname);
        }
    }
    else
    {
        printf("\nError: Currency %s does not exist in %s\n\n", currfrom, bankname);
    }
}

void delBank(PtrBankNode BankHead, char bankname[]) // deletes BankNode from list of BankNodes and deletes the adjaceny matrix of this bank if it exists
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrBankNode BankTrvPrev = BankHead;
    while (BankTrvPrev->next != BankTrv)
    {
        BankTrvPrev = BankTrvPrev->next;
    }
    BankTrvPrev->next = BankTrv->next;
    PtrCurrFromNode A = BankTrv->Currhead;
    PtrCurrFromNode P;
    while (A != NULL)
    {
        P = A;
        A = A->next;
        delCurr(BankHead, P->currname, bankname, 2);
    }
    free(BankTrv->Currhead);
    free(BankTrv);
    printf("\nDeleted bank %s\n\n", bankname);
}

void swapMinHeapNode(PtrPtrPQueueNode a, PtrPtrPQueueNode b) //swap 2 pqueue nodes,would be required as during heapify swapping is must
{
    PtrPQueueNode t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(PtrPQueue pQueue, int index) // heapify process is there to make PQueue follow the minheap condition
{                                            // that every node is smaller than its children
    int smallest, left, right;               // Here in this function we will also swap nodes and change their position in  position array
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;

    if (left < pQueue->size && pQueue->node[left]->dist < pQueue->node[smallest]->dist)
        smallest = left;

    if (right < pQueue->size && pQueue->node[right]->dist < pQueue->node[smallest]->dist)
        smallest = right;

    if (smallest != index)
    {
        PtrPQueueNode smallestNode = pQueue->node[smallest]; // Nodes which are neded to be swapped in minheap
        PtrPQueueNode idxNode = pQueue->node[index];         // so that condition of minheap is followed

        pQueue->position[smallestNode->n] = index; // here positions of nodes are changed
        pQueue->position[idxNode->n] = smallest;   // which would be swapped

        swapMinHeapNode(&pQueue->node[smallest], &pQueue->node[index]); // the nodes are swapped here

        minHeapify(pQueue, smallest); //need to recursively call this function to convert entire tree in minheap
    }
}

void decreaseKey(PtrPQueue pQueue, int n, int dist) // function to update the distance value(decrease distance particullarly) in heap nodes
{
    int i = pQueue->position[n]; // here position array is used to get the position of particular vertex in minheap directly

    pQueue->node[i]->dist = dist; // get to node with the help if i found above and update its distance value

    while (i && pQueue->node[i]->dist < pQueue->node[(i - 1) / 2]->dist) //travel up the tree while checking with parent that whether minheap condition is followed or not
    {
        pQueue->position[pQueue->node[i]->n] = (i - 1) / 2; // if minheap condition is not followed you will enter in loop
        pQueue->position[pQueue->node[(i - 1) / 2]->n] = i; // and keep on swapping node with parent untill minheap condition is not followed,swap position in position array also
        swapMinHeapNode(&pQueue->node[i], &pQueue->node[(i - 1) / 2]);

        i = (i - 1) / 2; ///go to next parent
    }
}

void bestConv(PtrBankNode BankHead, char currfrom[], char currto[])
{
    PtrBankNode BankTrv = BankHead;
    int bankno = BankHead->currno;
    store bank[bankno];
    int i = 0;
    bool error = 1;
    while (BankTrv->next != NULL)
    {
        BankTrv = BankTrv->next;
        if (CurrencyAlreadyPresent(BankTrv->Currhead, currfrom, 0) && CurrencyAlreadyPresent(BankTrv->Currhead, currto, 0))
        {
            error = 0;
            bank[i].cost = getList(BankHead, currfrom, currto, BankTrv->bankname);
        }
        else
        {
            bank[i].cost = max;
        }
        strcpy(bank[i].bankname, BankTrv->bankname);
        i++;
    }
    if (error == 1)
    {
        printf("\nError: No bank with conversion from %s to %s exists\n\n", currfrom, currto);
    }
    else
    {
        qsort(bank, bankno, sizeof(store), cmpfunc);
        if (bank[0].cost == max)
        {
            printf("\nError: No bank with conversion from %s to %s exists\n\n", currfrom, currto);
        }
        else
        {
            printf("\nThe best conversion rate from %s to %s exists in bank %s with conversion rate %d\n\n", currfrom, currto, bank[0].bankname, bank[0].cost);
        }
    }
}

int getList(PtrBankNode BankHead, char currfrom[], char currto[], char bankname[])
{
    //dijkstra

    //code to free the list
    //here we convert the adjacency matrix into an adjacency List to help us reduce time complexity

    int source;
    int dest;
    PtrBankNode BankTrv = findBank(BankHead, bankname); //Pointer BankTrv is a pointer that points to the Bank as entered by the user
    int n = BankTrv->currno;
    char index[n][20];
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    int i = 0;
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        strcpy(index[i], TrvCurrFrom->currname);
        i++;
    }

    for (int i = 0; i < n; i++)
    {
        if (strcmp(currfrom, index[i]) == 0)
        {
            source = i;

            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (strcmp(currto, index[i]) == 0)
        {
            dest = i;

            break;
        }
    }

    PtrListNode AdjList[n]; // This is the Adjacency List
    for (int i = 0; i < n; i++)
    {
        AdjList[i] = InitListNode(); // Initializing each node the Adjacency List
        AdjList[i]->index = i;       // The index of every Adjacency node is stored here
        PtrListNode TrvRow = AdjList[i];
        for (int j = 0; j < n; j++)
        {
            int conv = getConv(BankTrv->Currhead, index[i], index[j]); // Adding the cost of the edges to the edge nodes
            if (conv != 0)
            {
                PtrListNode P = InitListNode(); // Initialzing each node connected to the nodes of the Adj List
                P->currconv = conv;
                P->index = j;
                TrvRow->next = P;
                TrvRow = P;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d -> ", AdjList[i]->index);
        PtrListNode TrvRow = AdjList[i];
        while (TrvRow->next != NULL)
        {
            TrvRow = TrvRow->next;
            printf("(%d,%d) ", TrvRow->index, TrvRow->currconv);
        }
        printf("\n");
    }
    printf("\n");

    //Dijkstra
    int vertex = n;
    int v = vertex;
    int distance[v]; // distance array;
    //calling priority queue to make the algo more efficient

    PtrPQueue pq = createPQueue(v); // Creating a priority queue pq

    for (int i = 0; i <= v; i++)
    {

        distance[i] = max;                      //Initialzing the distance to infinity
        pq->node[i] = newPNode(i, distance[i]); // adding nodes to pq
        pq->position[i] = i;
    }
    distance[source] = 0;
    pq->position[source] = source;
    pq->size = v;
    decreaseKey(pq, source, distance[source]); // decreasing the cost/distance
    while (!isEmpty(pq))
    {
        PtrPQueueNode pqnode;
        pqnode = extractMin(pq); // extracting the root of the pq
        int x;
        x = pqnode->n;
        PtrListNode P = AdjList[x]->next; // pointer to the node of the source
        while (P != NULL)
        {
            int y;
            y = P->index;
            if (IsInPqueue(pq, y) && distance[x] != max && P->currconv + distance[x] < distance[y]) // relaxing the cost/distance array
            {
                distance[y] = distance[x] + P->currconv;
                decreaseKey(pq, y, distance[y]);
            }
            P = P->next;
        }
    }
    return distance[dest];
}

int cmpfunc(const void *p, const void *q) // comparator function in qsort
{
    Ptrstore u = (Ptrstore)p;
    Ptrstore v = (Ptrstore)q;
    return (u->cost - v->cost);
}

int getConv(PtrCurrFromNode P, char currfrom[], char currto[]) //returns conversion rate for conversion between 2 currencies
{
    P = findCurrFromNode(P, currfrom);
    PtrCurrToNode Q = findCurrToNode(P, currto);
    return Q->currconv;
}

int isEmpty(PtrPQueue pQueue) //to check if PQueue is empty or not
{
    return pQueue->size == 0; // if size is 0 that means there are no minheap nodes in our priority queue.
}
bool iscycle(PtrListNode P, bool visited[], bool stack[], PtrListNode AdjList[]) // recursive function to check if the nodes were visited before
{
    PtrListNode T = P;
    if (visited[T->index] == false)
    {
        visited[T->index] = true;
        stack[T->index] = true;
        P = AdjList[P->index];
        while (P->next != NULL)
        {
            P = P->next;
            // printf("%d\n", P->index);
            if (!visited[P->index] && iscycle(P, visited, stack, AdjList)) // recursively checking the iscycle function for vertices adjacent to the first one
            {
                //printf(" Go %d\n",P -> index);
                return true;
            }
            else if (stack[P->index])
            {
                return true;
            }
        }
    }
    stack[T->index] = false; // equal to removing the element of the stack
    return false;
}
bool cycle(PtrBankNode BankHead, char bankname[]) // finding the cycle using dfs
{
    PtrBankNode BankTrv = findBank(BankHead, bankname); // conversion of adjacency matrix to adjacency list same as the getList function
    int n = BankTrv->currno;
    char index[n][20];
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    int i = 0;
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        strcpy(index[i], TrvCurrFrom->currname);
        i++;
    }
    PtrListNode AdjList[n];
    for (int i = 0; i < n; i++)
    {
        AdjList[i] = InitListNode();
        AdjList[i]->index = i;
        PtrListNode TrvRow = AdjList[i];
        for (int j = 0; j < n; j++)
        {
            int conv = getConv(BankTrv->Currhead, index[i], index[j]);
            if (conv != 0)
            {
                PtrListNode P = InitListNode();
                P->currconv = conv;
                P->index = j;
                TrvRow->next = P;
                TrvRow = P;
            }
        }
    }

    bool visited[n]; //boolean array to store the visited nodes
    bool stack[n];   // boolean stack to keep a track of elements in the stack once you've visited the nodes connecting the given node
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        stack[i] = false;
    }
    // printf("hm %d\n",AdjList[0] -> index);
    for (int i = 0; i < n; i++)
    {
        PtrListNode P = AdjList[i];
        // printf("Hi %d\n", i);
        if (iscycle(P, visited, stack, AdjList))
        {
            return true;
        }
        printf("\n");
        // printf("%d\n",visited[i]);
    }

    return false;
}
