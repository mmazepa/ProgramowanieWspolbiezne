#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define klucz1 2005
#define klucz2 2608

// typedef struct
// {
//    char polish[100];
//    char english[100];
// } dictionary;

typedef struct
{
   long pID;
   char slowo[100];
} message;

int main(int argc, char *argv[]) {

  message communique;
  int input, output;

  input = msgget(klucz1, 0777);
  output = msgget(klucz2, 0777);

  strcpy(communique.slowo, argv[1]);
  communique.pID=getpid();

  if(msgsnd(input, &communique, sizeof(char)*110, 0) == -1) {
    printf("\nBłąd! Podczas wysyłania słowa do serwera");
    exit(1); }

  printf("J. polski: \"%s\" - ", argv[1]);

  if(msgrcv(output, &communique, sizeof(char)*110, getpid(), 0) == -1) {
    printf("\nBłąd! Podczas odbierania słowa od serwera");
    exit(2); }

  printf("J. angielski: \"%s\".\n", communique.slowo);

  return 0;
}
