#include "currency2.h"

PtrBankNode InitBankNode()
{
    PtrBankNode P = (PtrBankNode)malloc(sizeof(BankNode));
    P->currno = 0;
    P->Currhead = NULL;
    PtrCurrFromNode Temp = (PtrCurrFromNode)malloc(sizeof(CurrFromNode));
    Temp->FirstCurrTo = NULL;
    Temp->next = NULL;
    P->Currhead = Temp;
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

PtrList InitListNode()
{
    PtrList P = (PtrList)malloc(sizeof(List));
    P->index = 0;
    P->currconv = 0;
    P->next = 0;
    return P;
}

PtrBankNode findBank(PtrBankNode BankHead, char bankname[])
{
    PtrBankNode BankTrv = BankHead;
    while ((strcmp(BankTrv->bankname, bankname) != 0) && BankTrv->next != NULL)
    {
        BankTrv = BankTrv->next;
    }
    return BankTrv;
}

PtrCurrFromNode findCurrFromNode(PtrCurrFromNode TrvCurrFrom, char currname[])
{
    while(TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        if(strcmp(TrvCurrFrom->currname,currname) == 0)
        {
            return TrvCurrFrom;
        }
    }
}

PtrCurrToNode findCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[])
{
    PtrCurrToNode P = TrvCurrFrom->FirstCurrTo;
    while(strcmp(P->currname,currname) != 0)
    {
        P = P->next;
    }
    return P;
}

bool BankDoesntExist(PtrBankNode BankHead, char bankname[],int mode)
{
    PtrBankNode BankTrv = BankHead;
    while (BankTrv->next != NULL)
    {
        BankTrv = BankTrv->next;
        if (strcmp(BankTrv->bankname, bankname) == 0)
        {
            return 0;
        }
    }
    
    if(mode == 1)
    {
        printf("\nBank %s does not exist\n\n", bankname);
    }
    return 1;
}

bool NoBanksExist(PtrBankNode BankHead,int mode)
{
    PtrBankNode BankTrv = BankHead;
    if (BankTrv->next == NULL)
    {
        if(mode == 1)
        {
            printf("\nNo banks exist\n\n");
        }
        return 1;
    }
    return 0;
}

bool CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[],int mode)
{
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        if (strcmp(TrvCurrFrom->currname, currname) == 0)
        {
            if(mode == 1)
            {
                printf("\nError: Currency %s already exist\n\n", currname);
            }
            return 1;
        }
    }
    return 0;
}

bool NoCurrencyExists(PtrBankNode BankHead, char bankname[],int mode)
{
    PtrBankNode BankTrv = findBank(BankHead,bankname);
    if(BankTrv->currno == 0)
    {
        if(mode == 1)
        {
            printf("\nError: No currencies exists in bank %s\n\n",bankname);
        }
        return 1;
    }
    return 0;
}

void addBank(PtrBankNode BankHead, char bankname[])
{
    PtrBankNode BankTrv = findBank(BankHead," ");
    PtrBankNode Temp = InitBankNode();
    strcpy(Temp->bankname, bankname);
    BankTrv->next = Temp;
    Temp->next = NULL;
    printf("\nAdded bank %s\n\n", bankname);
}

void printBanks(PtrBankNode BankHead)
{
    printf("\n");
    PtrBankNode BankTrv = BankHead->next;
    while (BankTrv != NULL)
    {
        printf("%s ", BankTrv->bankname);
        BankTrv = BankTrv->next;
    }
    printf("\n\n"); 
}

PtrCurrFromNode addCurrFromNode(PtrCurrFromNode CurrHead, char currname[])
{
    while(CurrHead->next != NULL)
    {
        CurrHead = CurrHead->next;
    }
    PtrCurrFromNode Temp = InitCurrFromNode();
    strcpy(Temp->currname, currname);
    CurrHead->next = Temp;
    return Temp;
}

void addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[])
{
    if(TrvCurrFrom->FirstCurrTo == NULL)
    {
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrFrom->FirstCurrTo = temp;
    }
    else
    {
        PtrCurrToNode TrvCurrTo = TrvCurrFrom->FirstCurrTo;
        while(TrvCurrTo->next != NULL)
        {
            TrvCurrTo = TrvCurrTo->next;
        }
        PtrCurrToNode temp = InitCurrToNode();
        strcpy(temp->currname, currname);
        TrvCurrTo->next = temp;
    }
}

void addCurr(PtrBankNode BankHead, char bankname[], char currname[])
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    if(!CurrencyAlreadyPresent(TrvCurrFrom,currname,1))
    {
        PtrCurrFromNode NewCurr = addCurrFromNode(BankTrv->Currhead,currname);
        while(TrvCurrFrom->next != NewCurr)
        {
            TrvCurrFrom = TrvCurrFrom->next;
            addCurrToNode(TrvCurrFrom,currname);
            addCurrToNode(NewCurr,TrvCurrFrom->currname);
        }
        addCurrToNode(NewCurr,currname);
        (BankTrv->currno)++;
        printf("\nAdded currency %s to bank %s\n\n", currname, bankname);
    }

}

void printAllCurr(PtrBankNode BankHead,char bankname[])
{
    printf("\n\n"); 
    PtrBankNode BankTrv = findBank(BankHead, bankname);

    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    printf("\t\t");
    while (TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        PtrCurrToNode Q = TrvCurrFrom->FirstCurrTo;
        printf("%s\t\t", TrvCurrFrom->currname);
    }
    printf("\n\n");
    TrvCurrFrom = BankTrv->Currhead;
    while (TrvCurrFrom->next != NULL)
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

void delCurr(PtrBankNode BankHead, char currname[],char bankname[],int mode)
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    if(!CurrencyAlreadyPresent(TrvCurrFrom,currname,0))
    {
        if(mode == 1)
        {
            printf("\nError: Currency %s does not exist in bank %s\n\n", currname, bankname);
        }
    }
    else
    {
        PtrCurrFromNode Temp2 = findCurrFromNode(TrvCurrFrom,currname);
        PtrCurrFromNode Temp = BankTrv->Currhead;
        while(Temp->next != Temp2)
        {
            Temp = Temp->next;
        }
        (BankTrv->currno)--;

        if(Temp2 == BankTrv->Currhead->next)
        {
            PtrCurrFromNode TrvTemp = Temp2;
            while(TrvTemp->next != NULL)
            {
                TrvTemp = TrvTemp->next;
                PtrCurrToNode TrvRowTemp = TrvTemp->FirstCurrTo;
                TrvTemp->FirstCurrTo = TrvRowTemp->next;
                free(TrvRowTemp);
            }
            PtrCurrToNode RowTemp = Temp2->FirstCurrTo;
            while(RowTemp->next != NULL)
            {
                PtrCurrToNode Temp3 = RowTemp->next;
                RowTemp->next = Temp3->next;
                free(Temp3);
            }
            BankTrv->Currhead->next = Temp2->next;
            free(Temp2);
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
                while(strcmp(RowTemp->currname,currname) != 0)
                {
                    TrailRowTemp = RowTemp;
                    RowTemp = RowTemp->next;
                }
                TrailRowTemp->next = RowTemp->next;
                free(RowTemp);
            }
            PtrCurrToNode S = Temp2->FirstCurrTo;
            Temp->next = Temp2->next;
            while(S->next != NULL)
            {
                PtrCurrToNode Temp4 = S->next;
                S->next = Temp4->next;
                free(Temp4);
            }
            free(Temp2);
            printf("\nDeleted currency %s from bank %s\n\n", currname, bankname);
        }
    }
}

void findLoc(PtrCurrFromNode P, char currfrom[],char currto[],float currconv)
{
    P = findCurrFromNode(P,currfrom);
    PtrCurrToNode Q = findCurrToNode(P,currto);
    Q->currconv = currconv;
}

void addConv(PtrBankNode BankHead,char currfrom[],char currto[],float currconv, char bankname[], int mode)
{
    PtrBankNode BankTrv = findBank(BankHead, bankname);
    if(CurrencyAlreadyPresent(BankTrv->Currhead,currfrom,0))
    {
        if(CurrencyAlreadyPresent(BankTrv->Currhead,currto,0))
        {
            if(strcmp(currto,currfrom) == 0)
            {
                printf("\nError: Conversion between same currency not possible\n\n");
            }
            else
            {
                PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead; 
                findLoc(TrvCurrFrom,currfrom,currto,currconv);
                //findLoc(TrvCurrFrom,currto,currfrom,currconv);
                if(mode == 1)
                {
                    printf("\nAdded conversion %s to %s to bank %s\n\n", currfrom,currto, bankname);
                }
                else
                {
                    printf("\nDeleted conversion %s to %s in bank %s\n\n", currto,currfrom, bankname);
                } 
            }
        }
        else
        {
            printf("\nError: Currency %s does not exist in %s\n\n",currto,bankname);
        }
    }
    else
    {
        printf("\nError: Currency %s does not exist in %s\n\n",currfrom,bankname);
    }
}

void delBank(PtrBankNode BankHead,char bankname[])
{
    PtrBankNode BankTrv = findBank(BankHead,bankname);
    PtrBankNode BankTrvPrev = BankHead;
    while(BankTrvPrev->next != BankTrv)
    {
        BankTrvPrev = BankTrvPrev->next;
    }
    BankTrvPrev->next = BankTrv->next;
    PtrCurrFromNode A = BankTrv->Currhead;
    PtrCurrFromNode P;
    while(A != NULL)
    {
        P = A;
        A = A->next;
        delCurr(BankHead,P->currname,bankname,2);
    }
    free(BankTrv->Currhead);
    free(BankTrv);
    printf("\nDeleted bank %s\n\n",bankname);
}

int getConv(PtrCurrFromNode P, char currfrom[],char currto[])
{
    P = findCurrFromNode(P,currfrom);
    PtrCurrToNode Q = findCurrToNode(P,currto);
    return Q->currconv;
}

void getList(PtrBankNode BankHead,char bankname[])
{
    //dijkstra

    //code to free the list 
    PtrBankNode BankTrv = findBank(BankHead,bankname);
    int n = BankTrv->currno;
    char index[n][20];
    PtrCurrFromNode TrvCurrFrom = BankTrv->Currhead;
    int i = 0;
    while(TrvCurrFrom->next != NULL)
    {
        TrvCurrFrom = TrvCurrFrom->next;
        strcpy(index[i],TrvCurrFrom->currname);
        i++;
    }
    /*
    for(int i = 1; i <= n; i++)
    {
        printf("%s\n",index[i]);
    }
    */
    PtrList AdjList[n];
    for(int i = 0; i < n; i++)
    {
        AdjList[i] = InitListNode();
        AdjList[i]->index = i;
        PtrList TrvRow = AdjList[i];
        for(int j = 0; j < n; j++)
        {
            int conv = getConv(BankTrv->Currhead,index[i],index[j]);
            if(conv != 0)
            {
                PtrList P = InitListNode();
                P->currconv = conv;
                P->index = j;
                TrvRow->next = P;
                TrvRow = P;
            }
        }
    }
    
    for(int i = 0; i < n; i++)
    {
        printf("%d -> ",AdjList[i]->index);
        PtrList TrvRow = AdjList[i];
        while(TrvRow->next != NULL)
        {
            TrvRow = TrvRow->next;
            printf("(%d,%d) ",TrvRow->index,TrvRow->currconv);
        }
        printf("\n");
    }
    printf("\n");
}
