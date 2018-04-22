#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define klucz 15
#define GRACZ_1 'X'
#define GRACZ_2 'O'

int pamiec, semafor;
char *adres;
char symbol;

void end()
{
  semctl(semafor,0,IPC_RMID,0);
  shmdt(adres);
  shmctl(pamiec,IPC_RMID,0);
  exit(0);
}

void printPol()
{
  printf("  0|1|2\n");
  for(int i = 0; i< 3; i++)
  {
    printf("%d|",i);
    for(int j = 0; j < 3; j++)
    {
      printf("%c|",adres[i*3+j]);
    }
    printf("\n");
  }
}

void heuristic()
{
  for(int i = 0; i < 3; i++)
  {
    if(*(adres+i) == *(adres+i+3) && *(adres+i) == *(adres+i+6) && (*(adres+i) == GRACZ_1 || *(adres+i) == GRACZ_2))
    {
      printf("%c wygral\n",*(adres+i));
      end();
    }

    if(*(adres+i*3) == *(adres+i*3+1) && *(adres+i*3) == *(adres+i*3+2) && (*(adres+i*3) == GRACZ_1 || *(adres+i*3) == GRACZ_2))
    {
      printf("%c wygral\n",*(adres+i*3));
      end();
    }
  }

  if(*adres == *(adres+4) && *adres == *(adres+8) && (*adres == GRACZ_1 || *adres == GRACZ_2))
  {
    printf("%c wygral\n",*adres);
    end();
  }

  if(*(adres+2) == *(adres+4) && *(adres+2) == *(adres+6) && (*(adres+2) == GRACZ_1 || *(adres+2) == GRACZ_2))
  {
    printf("%c wygral\n",*(adres+2));
    end();
  }

  for (size_t i = 0; i < 9; i++)
  {
    if(*(adres+i) == ' ')
    {
      return;
    }
  }
  printf("REMIS\n");
  end();
}

void read()
{
  int num=-1;
  system("clear");
  printPol();
  while(num == -1)
  {
    printf("Podaj liczbe od 0 do 8 (nr pola):" );
    scanf("%d", &num);
    if(num>=0 && num <9)
    {
      if(*(adres+num) != GRACZ_1 && *(adres+num) != GRACZ_2)
      {
        *(adres+num) = symbol;
      }
      else
      {
        printf("Pole już zajęte\n");
        num = -1;
      }
    }
  }
  system("clear");
  printPol();
}

int main()
{
  struct sembuf oper0={0,-1,0},
                oper1={1,1,0},
                oper2={1,-1,0},
                oper3={0,1,0},
                * operX,
                * operO;
  pamiec=shmget(klucz,256,0777|IPC_CREAT);
  semafor=semget(klucz,2,0777|IPC_CREAT|IPC_EXCL);
  if(semafor != -1)
  { // X
    printf("!!!\n");
    symbol = GRACZ_1;
    operX = &oper0;
    operO = &oper1;
    semctl(semafor,0,SETVAL,1);
    semctl(semafor,1,SETVAL,0);
  }
  else
  { // 0
    semafor = semget(klucz,0,0777|IPC_CREAT);
    symbol = GRACZ_2;
    operX = &oper2;
    operO = &oper3;
  }

  printf("Grasz za %c\n", symbol );
  adres=shmat(pamiec,0,0);

  for(int i = 0; i<9; i++)
  {
    adres[i] = ' ';
  }

  while (1)
  {
    semop(semafor,operX,1);
    heuristic();
    read();
    heuristic();
    semop(semafor,operO,1);
  }
  return 0;
}
