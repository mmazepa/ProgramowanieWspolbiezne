#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <time.h>

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
  {"kot",         "cat"},         // #1
  {"pies",        "dog"},         // #2
  {"krowa",       "cow"},         // #3
  {"dzik",        "boar"},        // #4
  {"czas",        "time"},        // #5
  {"uniwersytet", "university"},  // #6
  {"kwiat",       "flower"},      // #7
  {"zegar",       "clock"},       // #8
  {"drzewo",      "tree"},        // #9
  {"mysz",        "mouse"},       // #10
  {"sieć",        "network"},     // #11
  {"samochód",    "car"},         // #12
  {"pająk",       "spider"},      // #13
  {"cegła",       "brick"},       // #14
  {"ścieżka",     "path"},        // #15
  {"wysiłek",     "effort"},      // #16
  {"nauka",       "science"},     // #17
  {"stos",        "stack"},       // #18
  {"wiedza",      "knowledge"},   // #19
  {"zadanie",     "task"}         // #20
};

char *przetlumacz(char* do_przetlumaczenia)
{
  int i;
  for(i = 0; i < rozmiar_slownika; i++)
  {
    if(!strcmp(do_przetlumaczenia, slownik_pl_ang[i].polski))
      return slownik_pl_ang[i].angielski;
  }
  return "Nie znam takiego slowa";
}

int main(int argc, char *argv[])
{
  Wiadomosc komunikat;
  int input, output;

  input = msgget(klucz1, 0777 | IPC_CREAT);
  output = msgget(klucz2, 0777 | IPC_CREAT);

  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");

  while(1)
  {
    if(msgrcv(input, &komunikat, sizeof(char)*110, 0, 0) == -1)
    {
      printf("[BŁĄD]: Odbiór słowa od klienta nie powiódł się!");
      exit(1);
    }

    printf("[SERWER]: Odebrano \"%s\" od PID[%ld], ", komunikat.slowo, komunikat.pID);
    strcpy(komunikat.slowo, przetlumacz(komunikat.slowo));
    printf("odsyłanie \"%s\".\n", komunikat.slowo);

    if(msgsnd(output, &komunikat, sizeof(char)*110, 0) == -1)
    {
       printf("\n[BŁĄD]: Wysyłanie słowa do klienta nie powiodło się!");
       exit(1);
     }
   }
   return 0;
}
