#include <stdio.h>

int main()
{
    int bankno;
    printf("Enter number of banks: ");
    scanf("%d",&bankno);
    char bankname[bankno][20];
    int currno[bankno];
    for(int i = 0; i < bankno; i++)
    {
        printf("Enter name of bank %d: ",i);
        scanf("%s",bankname[i]);
    }

}