#include <stdio.h>
main()
{
    int BT[15], TAT[15], WT[15];
    int i, n, totWT = 0, totTT = 0, p[15];
    int RT[15], t = 0, ts = 2, count = 0;
    float avgWT, avgTT;
    printf("Enter no.of processes : ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {
        printf("enter BT of p[%d] : ", i);
        scanf("%d", &BT[i]);
        p[i] = i;
        RT[i] = BT[i];
    }
    while (1)
    {
        for (i = 1; i <= n; i++)
        {
            if (RT[i] > 0)
            {
                if (RT[i] > ts)
                {
                    RT[i] = RT[i] - ts;
                    t = t + ts;
                }
                else if (RT[i] <= ts)
                {
                    t = t + RT[i];
                    RT[i] = 0;
                    TAT[i] = t;
                    count++;
                }
            }
        }
        if (count == n)
            break;
    }
    WT[1] = 0;
    for (i = 1; i <= n; i++)
    {
        WT[i] = TAT[i] - BT[i];
        totWT = t + WT[i];
        totTT = totTT + TAT[i];
    }
    avgWT = (float)totWT / n;
    avgTT = (float)totTT / n;
    printf("p.no\tBT\tWT\tTAT\n");
    for (i = 1; i <= n; i++)
    {
        printf("p[%d]\t%d\t%d\t%d\n", p[i], BT[i], WT[i], TAT[i]);
    }
    printf("\navgWT = %f", avgWT);
    printf("\navgTT = %f\n", avgTT);
}