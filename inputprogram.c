#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    int bankno;
    scanf("%d",&bankno);
    for(int i = 0; i < bankno; i++)
    {
        int currno;
        int density;
        scanf("%d",&currno);
        scanf("%d",&density);
        printf("addBank bank%d\n",i);
        for(int j = 0; j < currno; j++)
        {
            printf("addCurr curr%d bank%d\n",j,i);
        }
        for(int k = 0; k < currno; k++)
        {
            for(int l = 0; l < currno; l++)
            {
                if(k != l)
                {
                    if(rand() % density == 0 || rand() % density == 1)
                    {
                        printf("addConv curr%d curr%d %d bank%d\n",k,l,(rand() % 20) + 1,i);
                    }
                }
            }
        }
        printf("printAllCurr bank%d\n",i);
        printf("bestConv curr0 curr%d\n",currno - 1);
    }
    printf("exit\n");
}