

**1) Currency2.h -**

In this file we will declare 3 types of nodes- one for banks(bankNode), one for

the currency being converted from(currFromNode) and one for the currency

being converted to(currToNode) and their pointers. It will also declare a list

and include the function prototype for various functions that will be defined in

Currency.h.

bankNode-  This node stores the bank name(bankname[20]), currency

number(currno), a pointer to the next bank node(next) and a pointer to the first

“currency being converted from” node(Currhead).

currFromNode- This node stores the name of the currency being converted

from (currname[20]), pointer to the next “currency being converted from” node

in the list(next), pointer to the first “currency being converted to” node

(FirstcurrTo).

currToNode-  This node stores the name of the currency being converted to

(currname[20]), currency conversion rate (currconv), pointer to the next

currency being converted to (next).

List-  It will contain the index, currency conversion, and a pointer to the next.

**2) Currency2.c-**

In this file we will define the various functions that shall be called in main2.c.

InitBankNode()  - Declares pointer to bankNode, p, and mallocs memory to p

equivalent to size of bank node. It initializes values for all it’s elements and

returns p.

InitCurrFromNode() - Declares pointer to currFromNode, p, and mallocs

memory to p equivalent to size of currFromNode. It initializes values for all it’s

elements and returns p.

InitCurrToNode() - Declares pointer to currToNode, p, and mallocs memory to

p equivalent to size of currFromNode. It initializes values for all it’s elements

and returns p.





InitListNode() - Declares pointer to list, p, and mallocs memory to p equivalent

to size of List. It initializes values for all it’s elements and returns p.

findBank(PtrBankNode BankHead, char bankname[]) -

This function will search through the bank list until a bank with the required

name is found or the end of the list has been reached.

findcurrFromNode(PtrCurrFromNode TvrCurrFrom, char currname[]) -

This function will search through the “Currency From” list until the required

currency is found or the end of the list has been reached.

findcurrToNode(PtrCurrFromNode TvrCurrFrom, char currname[]) -

This function will search through the “Currency to” list from the FirstCurrTo

until the required currname is found or the end of the list has been reached.

BankDoesntExist(PtrBankNode BankHead, char bankname[ ], int mode ) -

A while loop is entered if the linked list is not empty i.e the next pointer of

BankHead doesn’t point to NULL. In this loop we search through the array

until we reach the end or a matching bank is found. If a match is found the

program returns 0 else prints a message saying the bank doesn’t exist and

returns 1.

NoBanksExist(PtrBankNode BankHead, int mode) -

An if statement checks if the next pointer of the BankHead points to null. If

true then a “No banks exist” message is printed and the function returns 1. If

not true then it returns 0.

CurrencyAlreadyPresent(PtrCurrFromNode TrvCurrFrom, char currname[], int mode) -

A while loop is entered and the list is searched through from the TrvCurrFrom

node(which is passed as parameter) until the last node of the list is reached or

a currency node with the required currency name is encountered. If the

currency is found then a “Currency already exists” message is printed and the

function returns 1 else it returns 0.





NoCurrencyExist(PtrBankNode BankHead, char bankname[ ], int mode) -

The findBank() function is called and the BankHead and bank name passed

as arguments to find the required bank. Upon finding it, if the currency

number(currno) is equal to 0 then the bank has no currencies and a “No

currencies exist” message is displayed and the function returns 1. Else if the

currno is not equal to 0, i.e currencies do exist then the function returns 0.

addBank(PtrBankNode BankHead,  char  bankname[]) -

This function calls the findBank() function and passes “ “ as a parameter for

bankname. Since no such bank exists, the function will search through the list

and return the address to the last bank which is stored in the pointer, BankTrv.

Then a new bank node is created by declaring a pointer to a bank node called

“Temp” and initializing it using the InitBankNode() function. Then the

bankname is copied to this node and is added to the list after BankTrv by

making BankTrv->next point to Temp and Temp->next point to NULL.

printBanks(PtrBankNode BankHead) -

Goes through the list and prints all the banknames until the final bank name

has been printed when the next pointer of the bank node points to NULL.

addCurrFromNode(PtrCurrFromNode CurrHead, char currname[ ])

A while loop is entered and the CurrHead(passed as argument) keeps shifting

the address to which it is pointing to the next node until it’s pointing to the last

node. Here a pointer to “currency from” node, called Temp, is declared and

initialized by calling function InitCurrFromNode(). Then the currency name is

copied to this node and it is added to the list linked to CurrHead.

addCurrToNode(PtrCurrFromNode TrvCurrFrom, char currname[ ])

If the first “currency to” node of TrvCurrFrom is NULL then a “currency to”

node pointed by Temp is declared and initialized by calling the

InitCurrToNode()





**3) main.c-**

**.** The first bank node, called BankHead, is initialized by calling InitBankNode()

function.

**.** The user is asked to input “command” specifying which task the user wishes

to perform.

**. “**strcmp” is used to compare the command input. A while loop is entered

which loops until the user enters the “exit” command. “strcmp” is used to

compare the string given as input by the user and match it to existing

commands. Upon finding a match, the necessary functions are called to

perform the task else a syntax error is displayed.

**>** If the command given is “addBank”, the user is asked to input the name of

the bank. The BankDoesntExist() function is called which returns 0 if a bank of

the same name exists and a 1 if it doesn’t. If the bank already exists an error

message is displayed or else the addBank function is called and the bank is

added to the list.

**>** If the command given is “printBank”, the NoBanksExist() function is called

and if it returns 0 i.e if banks do exist, then the printBanks() function is called

and all the bank names are printed.

**>** If the command given is “delBank”, the user inputs the bank name. The

BankDoesntexist function is called and if the bank exists then the delBank

function is called and the bank is deleted.

**>** If the command given is “addCurr”, the user inputs currency and bankname.

An if statement makes use of the NoBanksExist() and BankDoesntExist()

function to verify the existence of the bank of the same name. If it does exist

the addCurr() function is called and the currency is added to the bank.

**>** If the command given is “printAllCurr, the user inputs the bank name. An if

statement makes use of the NoBanksExist(), BankDoesntExist() and the

NoCurrencyExists() function to verify if a bank with the same name containing

currencies exists. If it does exist then the printAllCurr function is called to print

all the currencies.





**>** If the command given is “delCurr”, the user inputs the bank name and bank

currency name. An if statement uses the NoBanksExist(), BanksDoesntExist()

and the NoCurrencyExists functions to verify if a bank of the same name with

the same currency exists. If it exists then the deCurr() function is called to

delete the currency.

**>** If the command given is “addConv”, the user inputs the currency being

converted from and to, the bank name and the currency conversion. An if

statement uses the NoBanksExist(), BanksDoesntExist() functions to verify if a

bank of the same name exists. If it exists then the addConv() function is called

to add the conversion.

**>** If the command given is “getList”, the user inputs the bank name. The

getList function is called to get the linked list starting from the bank head.

**>** If neither of these commands is entered then a syntax error is displayed.

**.** The user is then required to input the command again. The while loop is the

reentered unless the user inputs

**4) Dijkstra\_starter.c-**

