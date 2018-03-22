#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define rozmiar_bazy 20
#define dlugosc_nazwiska 20

struct kom_cli2serv
{
  int liczba;
  int id;
  char* lancuch;
};

int main() {
  printf("hej, tu klient!");
  printf("\n");

  char* user_home;
  // user_home = system("echo $HOME");

  struct kom_cli2serv Komunikat;
  Komunikat.id = 1;
  Komunikat.lancuch = (char*)malloc(sizeof(char)*dlugosc_nazwiska);

  strncpy(Komunikat.lancuch, "Jedynkowski\0", dlugosc_nazwiska);

  printf("\n");
  return 0;
}
