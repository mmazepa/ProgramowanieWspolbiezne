#define _REENTRANT
#define _REENTRANT
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#define dimRows 3
#define dimCols 3
#define threads 10

int input[threads], output[threads];
int my_matrix[dimRows][dimCols];

void display_header()
{
  printf("╔═╗╔═╗╔═╗╦═╗ ╦  ╔╦╗╦ ╦╦═╗╔═╗╔═╗╔╦╗╔═╗\n");
  printf("╠═╝║ ║╚═╗║╔╩╦╝   ║ ╠═╣╠╦╝║╣ ╠═╣ ║║╚═╗\n");
  printf("╩  ╚═╝╚═╝╩╩ ╚═   ╩ ╩ ╩╩╚═╚═╝╩ ╩═╩╝╚═╝\n");
  printf("\n");
}

int sarrus(int m[dimRows][dimCols])
{
  int elem1 = m[0][0]*m[1][1]*m[2][2] + m[1][0]*m[2][1]*m[0][2] + m[2][0]*m[0][1]*m[1][2];
  int elem2 = m[0][2]*m[1][1]*m[2][0] + m[1][2]*m[2][1]*m[0][0] + m[2][2]*m[0][1]*m[1][0];
  return elem1 - elem2;
}

void *ff(void *matrix)
{
  // int new_matrix[dimRows][dimCols];
  // new_matrix = (int[dimRows][dimCols])matrix;
  unsigned long int liczba;
  liczba = (unsigned long int)matrix;

  // sleep(rand()%10);
  printf("[Wątek potomny] Start... liczba: %lu\n", liczba);
  // sleep(rand()%10);
  // input = sarrus(matrix);
  input[liczba] = liczba * liczba;
  printf("[Wątek potomny] Stop... miałem %lu, oddaję %d\n", liczba, input[liczba]);
  // pthread_exit(NULL);
  pthread_exit((void *)&input[liczba]);
  // return NULL;
}

main()
{
  system("clear");
  display_header();

  unsigned long int i, j = 0;
  int wyznacznik = 0;
  pthread_t tid[100];

  for (i = 0; i < threads; i++)
  {
    input[i] = 0;
    output[i] = 0;
  }

  my_matrix[0][0] = 2;
  my_matrix[0][1] = 3;
  my_matrix[0][2] = 5;
  my_matrix[1][0] = -1;
  my_matrix[1][1] = 4;
  my_matrix[1][2] = 6;
  my_matrix[2][0] = 3;
  my_matrix[2][1] = -2;
  my_matrix[2][2] = 7;

  for (i = 0; i < dimRows; i++)
  {
    printf("| ");
    for (j = 0; j < dimCols; j++)
    {
      printf(" %2d ", my_matrix[i][j]);
    }
    printf(" |\n");
  }
  printf("\n");

  for (i = 0; i < threads; i++)
  {
    // pthread_create(&tid+i,NULL,ff,(void **) my_matrix);
    pthread_create(&tid[i], NULL, ff, (void *) i);
  }

  for (i = 0; i < threads; i++)
  {
    // pthread_join(*(tid+1), NULL);
    int pthread_value = pthread_join(tid[i], (void **)&output[i]);
    if (pthread_value == 0)
    {
      printf("[Wątek rodzicielski] Wysłałem %lu, odebrałem %d\n", i, (int)output[i]);
    }
    else
    {
      printf("[%lu]: pthread_join not-ok! [error number: %d]\n", i, pthread_value);
    }
  }

  printf("\n");
  pthread_exit(NULL);
}
