#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

#define true 0
#define false 1

#define klucz1 2005
#define klucz2 2608

typedef struct {
  long pID;
  int red;
  int green;
  int blue;
} Kolor;

typedef struct
{
  long pID;
  Kolor kolor_przed;
  Kolor kolor_po;
} Przed_i_po;

void wyswietl_naglowek_klienta()
{
  printf(" _    _ _            _   \n");
  printf("| | _| (_) ___ _ __ | |_ \n");
  printf("| |/ / | |/ _ \\ '_ \\| __|\n");
  printf("|   <| | |  __/ | | | |_ \n");
  printf("|_|\\_\\_|_|\\___|_| |_|\\__|\n");
}

void fail(char *error_message)
{
  printf("[ERROR]: %s\n", error_message);
  exit(1);
}

int isValidNumber(char *string)
{
  int i;
  for (i = 0; i < strlen(string); i++)
  {
    if (string[i] < 48 || string[i] > 57)
    return false;
  }
  return true;
}

int areNumbersValid(char *str1, char *str2, char *str3)
{
  if (isValidNumber(str1) == false) return false;
  if (isValidNumber(str2) == false) return false;
  if (isValidNumber(str3) == false) return false;
  return true;
}

int main(int argc, char *argv[])
{
  Kolor kolor;
  Przed_i_po przed_i_po;

  int input, output;

  int kolor_red = 0;
  int kolor_green = 0;
  int kolor_blue = 0;

  input = msgget(klucz1, 0777);
  output = msgget(klucz2, 0777);

  // wyswietl_naglowek_klienta();
  // printf("--------------------------------------------------\n");

  if(!argv[1] || !argv[2] || !argv[3] || argv[4])
  {
    fail("Niepoprawna ilość argumentów, powinny być dokładnie 3!");
  }

  if (areNumbersValid(argv[1], argv[2], argv[3]) != 0)
  {
    fail("Argumenty powinny być liczbami naturalnymi!");
  }

  kolor_red = atoi(argv[1]);
  kolor_green = atoi(argv[2]);
  kolor_blue = atoi(argv[3]);

  if (kolor_red < 0 || kolor_green < 0 || kolor_blue < 0)
  {
    fail("Argumenty powinny być większe lub równe 0!");
  }

  if (kolor_red > 255 || kolor_green > 255 || kolor_blue > 255)
  {
    fail("Argumenty powinny być mniejsze lub równe 255!");
  }

  kolor.red = kolor_red;
  kolor.green = kolor_green;
  kolor.blue = kolor_blue;
  kolor.pID = getpid();

  if(msgsnd(input, &kolor, sizeof(int)*100, 0) == -1)
  {
    fail("Wysyłanie koloru do serwera nie powiodło się!");
  }

  // if(msgrcv(output, &przed_i_po, sizeof(int)*100, getpid(), 0) == -1)
  // {
  //   fail("Odbieranie koloru od serwera nie powiodło się!");
  // }
  //
  // printf("[kolor_serwera]: RGB(%3d %3d %3d)\n", przed_i_po.kolor_przed.red, przed_i_po.kolor_przed.green, przed_i_po.kolor_przed.blue);
  // printf("[podany_kolor]:  RGB(%3d %3d %3d)\n", kolor_red, kolor_green, kolor_blue);
  // printf("[kolor_serwera]: RGB(%3d %3d %3d)\n", przed_i_po.kolor_po.red, przed_i_po.kolor_po.green, przed_i_po.kolor_po.blue);

  return 0;
}
