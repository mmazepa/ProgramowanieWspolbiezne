#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define klucz1 2005
#define klucz2 2608

typedef struct
{
   long pID;
   char slowo[100];
} Wiadomosc;

int main(int argc, char* argv[])
{
  Wiadomosc komunikat;
  int input, output;

  input = msgget(klucz1, 0777);
  output = msgget(klucz2, 0777);

  if(!argv[1])
  {
    printf("[BŁĄD]: Nie podano argumentu!\n");
    exit(1);
  }

  strcpy(komunikat.slowo, argv[1]);
  komunikat.pID = getpid();

  if(msgsnd(input, &komunikat, sizeof(char)*110, 0) == -1)
  {
    printf("\n[BŁĄD]: Wysyłanie słowa do serwera nie powiodło się!");
    exit(1);
  }

  printf("J. polski: \"%s\" - ", argv[1]);

  if(msgrcv(output, &komunikat, sizeof(char)*110, getpid(), 0) == -1)
  {
    printf("\n[BŁĄD]: Odbieranie słowa od serwera nie powiodło się!");
    exit(1);
  }

  printf("J. angielski: \"%s\".\n", komunikat.slowo);

  return 0;
}
