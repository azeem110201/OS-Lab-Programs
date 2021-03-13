//Program to implement SSTF disk scheduling algorithm
#include <stdio.h>
#include <math.h>
main()
{
    int diskreq[20], temp[20], n, diskhdpos;
    int i, totseek = 0, min, diff, index, cnt, tpos;
    float avgdiskmove;
    printf("Enter the number of disk read requests\n");
    scanf("%d", &n);
    printf("Enter the [%d] disk read request positions \n", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &diskreq[i]);
        temp[i] = diskreq[i];
    }
    printf("Enter the initial disk head position\n");
    scanf("%d", &diskhdpos);
    cnt = 0;          // keeps track of completion of disk requests
    tpos = diskhdpos; // tpos used to keep track of the current disk head pos
    while (cnt < n)
    {
        min = 999999; // used to find the next disk request which causes least disk head movement
        for (i = 0; i < n; i++)
            if (temp[i] != -1)
            {
                diff = abs(diskreq[i] - tpos);
                if (min > diff)
                {
                    min = diff;
                    index = i; // index used to point to the next disk read request to service
                }
            }
        totseek += min;
        temp[index] = -1; // temp array is used to keep  track of completed requests.
        printf("Disk head movement from %d to %d is [%d] \n", tpos, diskreq[index], min);
        cnt++;
        tpos = diskreq[index];
        if (cnt == n)
            break;
    }

    avgdiskmove = (float)totseek / n;
    printf("Total seek time to process the above [%d] disk read requests is %d\n", n, totseek);
    printf("Average seek time to process the above disk read requests is %f\n", avgdiskmove);
}