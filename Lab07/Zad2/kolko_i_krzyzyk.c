#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define klucz 15
#define GRACZ_1 'X'
#define GRACZ_2 'O'

int pamiec, semafor;
char *adres;
char symbol;

// ------------------------------------------------------
// INFO, INFO, INFO !!!
// ------------------------------------------------------
//    1) Aplikacja odczytuje sygnały
//    2) Czyści pamięć na SIGINT i SIGTSTP
// ------------------------------------------------------
//    3) Zrobić tak, żeby wypisywało info o walkoverze
//       na obu planszach, jeśli ktoś straci "połączenie"
// ------------------------------------------------------

void koniec()
{
  semctl(semafor,0,IPC_RMID,0);
  shmdt(adres);
  shmctl(pamiec,IPC_RMID,0);
  exit(0);
}

void obsluga_sygnalow(int sygnal)
{
  if(sygnal == SIGINT)
  {
    printf("\n\nOdebrano sygnał SIGINT (ctrl+c)\n");
    printf("Czyszczenie pamięci współdzielonej.\n");
    koniec();
  }
  else if(sygnal == SIGTSTP)
  {
    printf("\n\nSIGTSTP sygnał (ctrl+z)\n");
    printf("Czyszczenie pamięci współdzielonej.\n");
    koniec();
  }
}

void czyszczenie_pamieci()
{
  signal(SIGINT, obsluga_sygnalow);
  signal(SIGTSTP, obsluga_sygnalow);
}

void rysuj_plansze()
{
  printf("[INFO]: Grasz jako %c.\n\n",symbol);

  printf("PLANSZA:\n\n");
  for(int i = 0; i< 3; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      if(j < 2)
      {
        printf(" %c |",adres[i*3+j]);
      }
      else
      {
        printf(" %c ",adres[i*3+j]);
      }
    }
    if(i < 2)
    {
        printf("\n---+---+---");
    }
    printf("\n");
  }
}

void rysuj_schemat()
{
  printf("\nSCHEMAT:\n\n");
  printf(" 1 | 2 | 3 \n");
  printf("---+---+---\n");
  printf(" 4 | 5 | 6 \n");
  printf("---+---+---\n");
  printf(" 7 | 8 | 9 \n");
}

void przerysuj_plansze()
{
  system("clear");
  rysuj_plansze();
}

void sprawdz_czy_ktos_wygral()
{
  for(int i = 0; i < 3; i++)
  {
    if(*(adres+i) == *(adres+i+3) && *(adres+i) == *(adres+i+6) && (*(adres+i) == GRACZ_1 || *(adres+i) == GRACZ_2))
    {
      przerysuj_plansze();
      printf("\nZwycięża %c!\n",*(adres+i));
      koniec();
    }

    if(*(adres+i*3) == *(adres+i*3+1) && *(adres+i*3) == *(adres+i*3+2) && (*(adres+i*3) == GRACZ_1 || *(adres+i*3) == GRACZ_2))
    {
      przerysuj_plansze();
      printf("\nZwycięża %c!\n",*(adres+i*3));
      koniec();
    }
  }

  if(*adres == *(adres+4) && *adres == *(adres+8) && (*adres == GRACZ_1 || *adres == GRACZ_2))
  {
    przerysuj_plansze();
    printf("\nZwycięża %c!\n",*adres);
    koniec();
  }

  if(*(adres+2) == *(adres+4) && *(adres+2) == *(adres+6) && (*(adres+2) == GRACZ_1 || *(adres+2) == GRACZ_2))
  {
    przerysuj_plansze();
    printf("\nZwycięża %c!\n",*(adres+2));
    koniec();
  }

  for(size_t i = 0; i < 9; i++)
  {
    if(*(adres+i) == ' ')
    {
      return;
    }
  }
  przerysuj_plansze();
  printf("\nREMIS!\n");
  koniec();
}

void podaj_ruch()
{
  int numer_pola = -1;
  przerysuj_plansze();
  rysuj_schemat();

  while(numer_pola == -1)
  {
    printf("\nPodaj liczbę z zakresu 1-9: ");
    scanf("%d", &numer_pola);
    numer_pola = numer_pola - 1;
    if(numer_pola == -1) koniec();
    if(numer_pola >= 0 && numer_pola < 9)
    {
      if(*(adres+numer_pola) != GRACZ_1 && *(adres+numer_pola) != GRACZ_2)
      {
        *(adres+numer_pola) = symbol;
      }
      else
      {
        printf("To pole jest już zajęte, wybierz inne!\n");
        numer_pola = -1;
      }
    }
    else
    {
      printf("Nie ma takiego pola!\n");
      numer_pola = -1;
    }
  }
  przerysuj_plansze();
}

int main (int argc, char *argv[])
{
  czyszczenie_pamieci();
  struct sembuf oper0={0,-1,0},
                oper1={1,1,0},
                oper2={1,-1,0},
                oper3={0,1,0},
                * operX,
                * operO;
  pamiec = shmget(klucz,256,0777|IPC_CREAT);
  semafor = semget(klucz,2,0777|IPC_CREAT|IPC_EXCL);
  if(semafor != -1)
  { // X
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

  // rozpoczęcie partii
  printf("Grasz jako \"%c\".\n", symbol);
  adres = shmat(pamiec,0,0);

  for(int i = 0; i < 9; i++)
  {
    adres[i] = ' ';
  }

  if(argv[1])
  {
    printf("Warunkowe czyszczenie pamięci współdzielonej.\n");
    koniec();
  }

  while(1)
  {
    semop(semafor,operX,1);
    sprawdz_czy_ktos_wygral();
    podaj_ruch();
    sprawdz_czy_ktos_wygral();
    semop(semafor,operO,1);
  }
  return 0;
}
