#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define max 1e5 + 5

typedef struct bankNode BankNode;
typedef struct bankNode * PtrBankNode;

typedef struct currFromNode CurrFromNode;
typedef struct currFromNode * PtrCurrFromNode;

typedef struct currToNode CurrToNode;
typedef struct currToNode * PtrCurrToNode;

typedef struct ListNode ListNode;
typedef struct ListNode *PtrListNode;

typedef struct PQueueNode PQueueNode;
typedef struct PQueueNode * PtrPQueueNode;
typedef struct PQueueNode ** PtrPtrPQueueNode;

typedef struct PQueue PQueue;
typedef struct PQueue * PtrPQueue;

typedef struct store store;
typedef struct store * Ptrstore;

struct bankNode //these nodes contain information about the banks that have been added
{
    char bankname[20]; //name of the bank
    int currno; //stores the number of currencies in the bank
    PtrBankNode next; // points to the next bankNode
    PtrCurrFromNode Currhead; //points to the first node in the adjacency matrix
};


// Every conversion is done FROM a currency TO a currency, so 2 different structs have been defined for the same
// Currencies in each bank are stored in the form of adjacency matrix


struct currFromNode //CurrFromNodes are head pointers for the link list of CurrToNodes
{
    char currname[20]; //name of the currency
    PtrCurrFromNode next; //points to the next CurrFromNode
    PtrCurrToNode FirstCurrTo; //points to the first CurrToNode
};

struct currToNode
{
    char currname[20];
    float currconv; //stores the conversion rate of the currency name of the currFromNode this node is linked to, to the currency that currname of this node stores.
    PtrCurrToNode next; //points to the next CurrToNode
};

struct ListNode //struct for the adjacency list
{
    int index; //index of each node in the graph
    int currconv; //stores the weight of each edge in the graph, which is the conversion rate
    PtrListNode next; //points to the next List node
};

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
    PtrPtrPQueueNode node; //Will point to PqueueNode or minheap nodes
};

struct store
{
    int cost;
    char bankname[20];
};

PtrBankNode InitBankNode();
PtrBankNode findBank(PtrBankNode BankHead, char bankname[]);

PtrCurrFromNode InitCurrFromNode();
PtrCurrFromNode findCurrFromNode(PtrCurrFromNode TrvCurrFrom, char currname[]);
PtrCurrFromNode addCurrFromNode(PtrCurrFromNode CurrHead, char currname[]);

PtrCurrToNode InitCurrToNode();
PtrCurrToNode findCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]);

PtrListNode InitListNode();

struct PQueueNode *newPNode(int n, int dist);
struct PQueueNode *extractMin(struct PQueue *pQueue);

struct PQueue *createPQueue(int capacity);

bool BankDoesntExist(PtrBankNode BankHead, char bankname[],int mode);
bool NoBanksExist(PtrBankNode BankHead,int mode);
bool CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[],int mode);
bool NoCurrencyExists(PtrBankNode BankHead, char bankname[],int mode);
bool IsInPqueue(struct PQueue *pQueue, int n);

void addBank(PtrBankNode BankHead, char bankname[]);
void printBanks(PtrBankNode BankHead);
void addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[]);
void addCurr(PtrBankNode BankHead, char bankname[], char currname[]);
void printAllCurr(PtrBankNode BankHead,char bankname[]);
void delCurr(PtrBankNode BankHead, char currname[],char bankname[],int mode);
void findLoc(PtrCurrFromNode P, char currfrom[],char currto[],float currconv);
void addConv(PtrBankNode BankHead,char currfrom[],char currto[],float currconv, char bankname[], int mode);
void delBank(PtrBankNode BankHead,char bankname[]);
void swapMinHeapNode(struct PQueueNode **a, struct PQueueNode **b);
void minHeapify(struct PQueue *pQueue, int index);
void decreaseKey(struct PQueue *pQueue, int n, int dist);
void bestConv(PtrBankNode BankHead,char currfrom[],char currto[]);

int cmpfunc(const void *p, const void *q);
int isEmpty(struct PQueue *pQueue);
int getConv(PtrCurrFromNode P, char currfrom[], char currto[]);
int getList(PtrBankNode BankHead, char currfrom[], char currto[], char bankname[]);