#include <X11/Xlib.h>
#include <X11/X.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>
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

XColor przygotuj_xcolor(int red, int green, int blue)
{
  XColor newColor;
  newColor.red = (red * 65535)/257;
  newColor.green = (green * 65535)/257;
  newColor.blue = (blue * 65535)/257;
  return newColor;
}

Kolor przygotuj_kolor(char *argv[])
{
  int kolor_red, kolor_green, kolor_blue;
  Kolor kolor;

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

  return kolor;
}
