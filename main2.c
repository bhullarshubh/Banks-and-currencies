#include "currency2.c"

/************************************************************
 *          TRADE BANK MANAGEMENT USER INTERFACE            *
 *                         GROUP-4                          *
 *                                                          *
 *  MEMBERS                                                 *
 *  1. Prerak Srivastava                                    *
 *  2. KNV Karthikeya                                       *
 *  3. Shubh Bhullar                                        *
 *  4. Rohan Maddeini                                       *
 *                                                          *
 *                                                          *    
 *                                                          *
 *                                                          *
 *                                                          *
 * *********************************************************/


int main()
{
    printf(YELLOW);
    printf("type 'commands' to see list of commands\n");
    printf(RESET);
    PtrBankNode BankHead = InitBankNode();
    char command[20];
    printf(PURPLE);
    printf("> ");
    printf(RESET);
    scanf("%s", command);
    while (strcmp(command, "exit") != 0)
    {
        if (strcmp(command, "addBank") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if (!BankDoesntExist(BankHead, bankname, 0))
            {
                printf(RED);
                printf("\nError: Bank %s already exist\n\n", bankname);
                printf(RESET);
            }
            else
            {
                addBank(BankHead, bankname);
                BankHead->currno++;
            }
        }
        else if (strcmp(command, "printBank") == 0)
        {
            if (!NoBanksExist(BankHead, 1))
            {
                printBanks(BankHead);
            }
        }
        else if (strcmp(command, "delBank") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if (!BankDoesntExist(BankHead, bankname, 1))
            {
                delBank(BankHead, bankname);
                BankHead->currno--;
            }
        }
        else if (strcmp(command, "addCurr") == 0)
        {
            char currname[20];
            char bankname[20];
            scanf("%s %s", currname, bankname);
            if ((!NoBanksExist(BankHead, 1)) && (!BankDoesntExist(BankHead, bankname, 1)))
            {
                addCurr(BankHead, bankname, currname);
            }
        }
        else if (strcmp(command, "printAllCurr") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            if ((!NoBanksExist(BankHead, 1)) && (!BankDoesntExist(BankHead, bankname, 1)) && (!NoCurrencyExists(BankHead, bankname, 1)))
            {
                printAllCurr(BankHead, bankname);
            }
        }
        else if (strcmp(command, "delCurr") == 0)
        {
            char currname[20];
            char bankname[20];
            scanf("%s %s", currname, bankname);
            if ((!NoBanksExist(BankHead, 1)) && (!BankDoesntExist(BankHead, bankname, 1)) && (!NoCurrencyExists(BankHead, bankname, 1)))
            {
                delCurr(BankHead, currname, bankname, 1);
            }
        }
        else if (strcmp(command, "addConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            float currconv;
            scanf("%s %s %f %s", currfrom, currto, &currconv, bankname);
            if ((!NoBanksExist(BankHead, 1)) && (!BankDoesntExist(BankHead, bankname, 1)))
            {
                addConv(BankHead, currfrom, currto, currconv, bankname, 1);
            }
        }
        else if (strcmp(command, "delConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            char bankname[20];
            scanf("%s %s %s", currfrom, currto, bankname);
            if ((!NoBanksExist(BankHead, 1)) && (!BankDoesntExist(BankHead, bankname, 1)))
            {
                addConv(BankHead, currfrom, currto, 0, bankname, 0);
            }
        }
        else if (strcmp(command, "bestConv") == 0)
        {
            char currfrom[20];
            char currto[20];
            scanf("%s", currfrom);
            scanf("%s", currto);
            bestConv(BankHead,currfrom,currto);
        }
        else if (strcmp(command, "commands") == 0)
        {
            printf(YELLOW);
            printf("\n1. addBank bankname\n");
            printf("2. printBank\n");
            printf("3. delBank bankname\n");
            printf("4. addCurr currname bankname\n");
            printf("5. printAllCurr bankname\n");
            printf("6. delCurr currname bankname\n");
            printf("7. addConv currfrom currto currconv bankname\n");
            printf("8. delConv currfrom currto bankname\n");
            printf("9. bestConv currfrom currto\n");
            printf("10. findCycle bankname\n\n");
            printf("11. exit\n\n");
            printf(RESET);
        }
        else if (strcmp(command, "findCycle") == 0)
        {
            char bankname[20];
            scanf("%s", bankname);
            PtrBankNode BankTrv = BankHead->next;
            if (cycle(BankTrv, bankname) == true)
            {
                printf(GREEN);
                printf("\nA cycle between the currencies exists in bank %s\n", bankname);
                printf(RESET);
            }
            else
            {
                printf(RED);
                printf("\nError: No cycles exist in bank %s\n", bankname);
                printf(RESET);
            }
        }
        else
        {
            printf("Syntax Error\n");
        }
        printf(PURPLE);
        printf("> ");
        printf(RESET);
        scanf("%s", command);
    }
    
    printf("\n");
}
