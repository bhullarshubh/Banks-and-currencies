#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++)
    {
        int c;
        scanf("%d",&c);
        printf("addBank bank%d\n",i);
        for(int j = 1; j <= c; j++)
        {
            printf("addCurr curr%d bank%d\n",j,i);
        }
        for(int k = 1; k<= c; k++)
        {
            for(int l = 1; l <= c; l++)
            {
                if(k != l)
                {
                    printf("addConv curr%d curr%d %d bank%d\n",k,l,rand() % 10,i);
                }

            }
            printf("bestConv curr1 curr%d\n",c);
        }
        printf("printAllCurr bank%d\n",i);
    }
    printf("exit\n");
}