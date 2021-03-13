#include <stdio.h>
main()
{
    int BT[15], TAT[15], WT[15];
    int i, n, j, temp, totWT = 0, totTT = 0, p[15];
    float avgWT, avgTT;
    printf("Enter no.of processes : ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("Enter BT of p[%d] : ", i + 1);
        scanf("%d", &BT[i]);
        p[i] = i;
    }
    for (i = 1; i <= n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (BT[j] < BT[i])
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
                
                temp = BT[i];
                BT[i] = BT[j];
                BT[j] = temp;
            }
        }
    }
    WT[1] = 0;
    TAT[1] = WT[1] + BT[1];
    totWT = WT[1];
    totTT = TAT[1];
    for (i = 2; i <= n; i++)
    {
        WT[i] = WT[i - 1] + BT[i - 1];
        TAT[i] = WT[i] + BT[i];
        totWT = totWT + WT[i];
        totTT = totTT + TAT[i];
    }
    avgWT = (float)totWT / n;
    avgTT = (float)totTT / n;
    printf("p.no\tBT\tWT\tTAT\n");
    for (i = 1; i <= n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", p[i], BT[i], WT[i], TAT[i]);
    }
    printf("\navgWT = %f", avgWT);
    printf("\navgTT =%f\n\n", avgTT);
}