#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define klucz1 2005
#define klucz2 2608

typedef struct {
  long pID;
  int red;
  int green;
  int blue;
} Kolor;

void wyswietl_naglowek(char *program)
{
  if (strcmp(program, "serwer") == 0)
  {
    printf(" ___  ___ _ ____      _____ _ __ \n");
    printf("/ __|/ _ \\ '__\\ \\ /\\ / / _ \\ '__|\n");
    printf("\\__ \\  __/ |   \\ V  V /  __/ |   \n");
    printf("|___/\\___|_|    \\_/\\_/ \\___|_|   \n");
  }

  if (strcmp(program, "klient") == 0)
  {
    printf(" _    _ _            _   \n");
    printf("| | _| (_) ___ _ __ | |_ \n");
    printf("| |/ / | |/ _ \\ '_ \\| __|\n");
    printf("|   <| | |  __/ | | | |_ \n");
    printf("|_|\\_\\_|_|\\___|_| |_|\\__|\n");
  }
}

void fail(char *error_message)
{
  printf("[ERROR]: %s\n", error_message);
  exit(1);
}
