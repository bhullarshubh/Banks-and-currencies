#include "currency2.c"



int main()
{
    PtrBankNode BankHead = InitBankNode();
    char command[20];
    printf("> ");
    scanf("%s", command);
    while(strcmp(command, "exit") != 0)
    {
        if(strcmp(command, "addBank") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if(!BankDoesntExist(BankHead,bankname,0))
            {
                printf("\nError: Bank %s already exist\n\n", bankname);
            }
            else
            {
                addBank(BankHead, bankname);
            }     
        }
        else if(strcmp(command, "printBank") == 0)
        {
            if(!NoBanksExist(BankHead,1))
            {   
                printBanks(BankHead);
            }            
        }
        else if(strcmp(command, "delBank") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if(!BankDoesntExist(BankHead,bankname,1))
            {
                delBank(BankHead,bankname);
            }
        }
        else if(strcmp(command, "addCurr") == 0)
        {
            char currname[20];
            char bankname[20];
            scanf("%s %s", currname, bankname);
            if((!NoBanksExist(BankHead,1)) && (!BankDoesntExist(BankHead, bankname,1)))
            {
                addCurr(BankHead,bankname,currname);
            }
        }
        else if(strcmp(command, "printAllCurr") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if((!NoBanksExist(BankHead,1)) && (!BankDoesntExist(BankHead, bankname,1)) && (!NoCurrencyExists(BankHead,bankname,1)))
            {
                printAllCurr(BankHead,bankname);
            }
            
        }
        else if (strcmp(command, "delCurr") == 0)
        {
            char currname[20];
            char bankname[20];
            scanf("%s %s", currname,bankname);
            if((!NoBanksExist(BankHead,1)) && (!BankDoesntExist(BankHead, bankname,1)) && (!NoCurrencyExists(BankHead,bankname,1)))
            {
                delCurr(BankHead,currname,bankname,1);
            }
            
        }
        else if (strcmp(command, "addConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            float currconv;
            scanf("%s %s %f %s", currfrom,currto,&currconv,bankname);
            if((!NoBanksExist(BankHead,1)) && (!BankDoesntExist(BankHead, bankname,1)))
            {
                addConv(BankHead,currfrom,currto,currconv,bankname,1);
            }
        }
        else if (strcmp(command, "delConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            scanf("%s %s %s", currfrom,currto,bankname);
            if((!NoBanksExist(BankHead,1)) && (!BankDoesntExist(BankHead, bankname,1)))
            {
                addConv(BankHead,currfrom,currto,0,bankname,0);
            }
        }
        else if (strcmp(command, "bestConv") == 0)
        {
           
            char currfrom[20];
            char currto[20];
            scanf("%s",currfrom);
            scanf("%s",currto);
            char bankname[20];
            scanf("%s",bankname);
            getList(BankHead,currfrom,currto,bankname);
        }
        else if (strcmp(command, "commands") == 0)
        {

        }
        else
        {
            printf("Syntax Error\n");
        }
        printf("> ");
        scanf("%s", command);
    }
}