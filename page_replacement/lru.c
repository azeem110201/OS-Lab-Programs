// Program to implement LRU page replacement algorithm
#include <stdio.h>
#include <stdlib.h>
main()
{
    int prs[30], frame[10];
    int prslen, frlen, pf;
    int i, j, k, flag, flag1, prevloc, loc, min;
    system("clear");

    printf("\n enter the page reference string length \t"); //Read page reference string Length
    scanf("%d", &prslen);
    printf("\n enter the frame length \t:"); // Read the Memory Frame size
    scanf("%d", &frlen);
    for (i = 0; i < frlen; i++) // Initialize frame elements to -1
        frame[i] = -1;
    printf("\n enter the [%d] page reference string elements", prslen);
    for (i = 0; i < prslen; i++) // Read Reference String Elements
    {
        printf("\n enter PRS[%d] \t element value: \t:", i);
        scanf("%d", &prs[i]);
    }
    printf("\n"); // printing the input page reference string read from keyboard
    printf("Page Reference String is \n: ");
    for (i = 0; i < prslen; i++)
        printf(" %d\t:", prs[i]);
    printf("\n");

    printf("\n PRS# \t Frame Elements Sequence \t Pgflt#\n");
    pf = 0; // total page faults is initialized to 0
    for (i = 0; i < prslen; i++)
    {
        flag = 0;                   // used to check page exists in memory status
        for (j = 0; j < frlen; j++) //this loop checks if the page is in memory
            if (prs[i] == frame[j])
            {
                flag = 1;
                break;
            }
        if (flag == 1) // no page fault - printing the output line
        {
            printf("%d \t", prs[i]);
            for (j = 0; j < frlen; j++)
                printf("%d\t", frame[j]);
            printf("\t %d \n", pf);
            continue;
        }
        if (flag == 0) // page is not in memory
        {
            flag1 = 0;                  //used to check if free frame found status
            for (j = 0; j < frlen; j++) // this loop checks if free frame exists
                if (frame[j] == -1)
                {
                    frame[j] = prs[i]; // then inserts the page in that location
                    pf++;
                    flag1 = 1;
                    break;
                }
            if (flag1 == 1) // free frame found so print the  output
            {
                printf("%d \t", prs[i]);
                for (j = 0; j < frlen; j++)
                    printf("%d\t", frame[j]);
                printf("\t %d \n", pf);
                continue;
            }
            if (flag1 == 0) // need to do page replacement
            {
                min = 100; // min will point to prs 
                prevloc = 0;//will point to not recently used frame ...
                for (j = 0; j < frlen; j++) 
                {
                   for (k = i - 1; k >= 0; k--) // get the loc of frame element j in PRS
                        if  (prs[k] == frame[j])
                        {
                            loc = k;
                            break;
                        }
                    if (min > loc)
                    {
                        min = loc;
                        prevloc = j;
                    }
                }
                frame[prevloc] = prs[i]; //insert the page in the frame
                pf++;                    // increment page fault
            }
        }
        printf("%d \t", prs[i]); // code to print output
        for (j = 0; j < frlen; j++)
            printf("%d\t", frame[j]);
        printf("\t %d \n", pf);
    } // end of processing reference string pages
}