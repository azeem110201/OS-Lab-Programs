#include <stdio.h>
#include <stdlib.h>
int mutex = 1, full = 0, empty, x = 0;
main()
{
    //full shows how many items are there in the buffer at the moment..it is like size of buffer ..
    //if full is 0 then it means buffer has no items and so consumer can not consume anything
    //empty shows hom many items can be stored in the buffer at the moment ...it shows empty space available in the buffer 
    //if empty is 0 then buffer is full or there is not empty space available ...and hence producer can not produce anything and he has to
    //wait till consumer consumes an item

    //mutex is used to make process i.e prdocuer and consumer synchornus 
    //if producer is producing something then consumer can not consume and vise versa
    int n, size;
    void producer();
    void consumer();
    int wait(int);
    int signal(int);
    printf("Enter the size :");
    scanf("%d", &size);
    empty = size;
    printf("\n1.producer\n2.consumer\n3.exit\n");
    while (1)
    {
        printf("\nEnter your choice : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
                producer();
            else
                printf("buffer is full\n");
            break;
        case 2:
            if ((mutex == 1) && (full != 0))
                consumer();
            else
                printf("buffer is empty\n");
            break;
        case 3:
            exit(0);
        }
    }
}
void producer()
{
    mutex = wait(mutex);
    full = signal(full);
    empty = wait(empty);
    x++;
    printf("producer produces the item %d\n", x);
    mutex = signal(mutex);
}
void consumer()
{
    mutex = wait(mutex);
    full = wait(full);
    empty = signal(empty);
    printf("consumer consumes the item %d\n", x);
    x--;
    mutex = signal(mutex);
}
int wait(s)
{
    //1 ..0
    return (--s);
}
int signal(s)
{
    //0..1
    return (++s);
}