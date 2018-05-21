#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int x,*y;

void *ff()
{
   printf("To ja, watek potomny !\n");
   printf("Jaka wartosc mam przekazac ? ");
   scanf("%5d",&x);
   pthread_exit((void *)&x);
}

main()
{
   pthread_t tid;

   pthread_create(&tid,NULL,ff,NULL);
   pthread_join(tid,(void **) &y);
   printf("To ja, watek rodzicielski !\n");
   printf("Wartosc odebrana: %5d \n",*y);
   exit(0);
}
