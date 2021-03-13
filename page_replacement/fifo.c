// Program to demonstrate FIFO page replacement algorithm
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int Pg[15] = {0}, Fr[15] = {0};
    int n, s, ptr, cnt;
    int i, j, flag;
    printf("\n Enter length of page reference string:");
    scanf("%d", &n);
    printf("\n Enter no.of frames :");
    scanf("%d", &s);
    printf("\n enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &Pg[i]);
    ptr = 0;
    for (i = 0; i < n; i++)
    {
        flag = 0;
        for (j = 0; j < s; j++) // checking if the page is already in memory
            if (Pg[i] == Fr[j])
            {
                flag = 1;
                break;
            }
        if (flag == 0)
        {
            cnt++;
            Fr[ptr] = Pg[i];
            ptr=(ptr+1)%n;
        }
    }
    printf("\n No.of page faults = %d\n", cnt);
}