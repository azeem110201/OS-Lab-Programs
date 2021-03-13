#include <stdio.h>
main()
{
    int BT[15], TAT[15], WT[15];
    int i, n, totWT = 0, totTT = 0, p[15];
    float avgWT, avgTT;
    printf("Ener no.of processes : ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("Enter BT of p[%d] : ", i);
        scanf("%d", &BT[i]);
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
        printf("p[%d]\t%d\t%d\t%d\n", i, BT[i], WT[i], TAT[i]);
    }
    printf("\navgWT = %f", avgWT);
    printf("\navgTT =%f\n\n", avgTT);
}