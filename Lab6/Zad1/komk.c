#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

// #define klucz 10

struct komunikat
{
  long typ;
  char dane[256];
};

void main()
{
  struct komunikat kom;
  int kolejka, *wsk;
  long ident;

  char *sciezka = "Wspolbiezne/Lab6/Zad1";
  key_t kluczyk = ftok(sciezka, getpid());
  // printf("%s\n%5d\n%d", sciezka, getpid(), kluczyk);

  kolejka=msgget(kluczyk,0777);
  ident=getpid();
  wsk=(int*) kom.dane;
  *wsk=5;
  kom.typ=ident;
  msgsnd(kolejka,&kom,sizeof(int),0);
  printf("klient %5li: wyslalem   %5d\n", ident, *wsk);
  msgrcv(kolejka,&kom,sizeof(int),ident,0);
  printf("klient %5li: otrzymalem %5d\n", ident, *wsk);
}
