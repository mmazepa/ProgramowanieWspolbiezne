#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define rozmiar_slownika 20
#define klucz1 2005
#define klucz2 2608

typedef struct {
  char polski[100];
  char angielski[100];
} Slownik;

typedef struct {
  long pID;
  char slowo[100];
} Wiadomosc;

Slownik slownik_pl_ang[rozmiar_slownika] = {
  {"rower", "bike"}, {"kot", "cat"},
  {"pies", "dog"}, {"owca", "lamb"},
  {"stół", "table"}, {"krzesło", "chair"},
  {"mleko", "milk"}, {"zegar", "clock"},
  {"prysznic", "shower"}, {"blisko", "near"},
  {"dom", "house"}, {"samochód", "car"},
  {"grać", "play"}, {"brać", "take"},
  {"chwila", "while"}, {"drzewo", "tree"},
  {"dzwonić", "call"}, {"głowa", "head"},
  {"każdy", "each"}, {"który", "which"}
};

char *translate(char*);
void endWork(int);
void clQueve(int);

int input, output;

int main(int argc, char *argv[])
{
  Wiadomosc komunikat;
  input = msgget(klucz1, 0777 | IPC_CREAT);
  output = msgget(klucz2, 0777 | IPC_CREAT);

  while(1)
  {
    if(msgrcv(input, &komunikat, sizeof(char)*110, 0, 0) == -1)
    {
      printf("[BŁĄD]: Odbiór słowa od klienta nie powiódł się!");
      exit(1);
    }

    printf("Odebrano: \"%s\", ", komunikat.slowo);
    strcpy(komunikat.slowo, translate(komunikat.slowo));
    printf("wysylanie do PID[%5ld] odpowiedz \"%s\".\n", komunikat.pID, komunikat.slowo);

    if(msgsnd(output, &komunikat, sizeof(char)*110, 0) == -1)
    {
       printf("\n[BŁĄD]: Wysyłanie słowa do klienta nie powiodło się!");
       exit(1);
     }
   }
   return 0;
}

char *translate(char* do_przetlumaczenia)
{
  int i;
  for(i = 0; i < rozmiar_slownika; i++)
  {
    if(!strcmp(do_przetlumaczenia, slownik_pl_ang[i].polski))
      return slownik_pl_ang[i].angielski;
  }
  return "Nie znam takiego slowa.";
}
