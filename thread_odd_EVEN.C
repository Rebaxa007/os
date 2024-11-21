#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* even(void *arg)
{
    for(int i=0;i<20;i++)
    {
        if(i%2==0)
        {
            printf("Even: %d\n",i);
        }
    }
    return NULL;
}

void* odd(void *arg)
{
    for(int i=0;i<20;i++)
    {
        if(i%2!=0)
        {
            printf("Odd: %d\n",i);
        }
    }
    return NULL;
}

int main()
{
    pthread_t odd_t, even_t;

    pthread_create(&odd_t,NULL,odd,NULL);
    pthread_create(&even_t,NULL,even,NULL);

    pthread_join(even_t,NULL);
    pthread_join(odd_t,NULL);

    return 0;
}