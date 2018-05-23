#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

Kolor zmieszaj(int wartosc_red, int wartosc_green, int wartosc_blue, Kolor kolor, Kolor kolor_na_serwerze)
{
  kolor.red = (kolor_na_serwerze.red + wartosc_red)/2;
  kolor.green = (kolor_na_serwerze.green + wartosc_green)/2;
  kolor.blue = (kolor_na_serwerze.blue + wartosc_blue)/2;
  return kolor;
}

void wyswietl_naglowek_serwera()
{
  printf(" ___  ___ _ ____      _____ _ __ \n");
  printf("/ __|/ _ \\ '__\\ \\ /\\ / / _ \\ '__|\n");
  printf("\\__ \\  __/ |   \\ V  V /  __/ |   \n");
  printf("|___/\\___|_|    \\_/\\_/ \\___|_|   \n");
}

int main(int argc, char *argv[])
{
  system("clear");

  Kolor kolor_na_serwerze;
  Kolor kolor;
  Przed_i_po przed_i_po;

  int input, output;

  kolor_na_serwerze.red = 0;
  kolor_na_serwerze.green = 0;
  kolor_na_serwerze.blue = 0;
  kolor_na_serwerze.pID = getpid();

  input = msgget(klucz1, 0777 | IPC_CREAT);
  output = msgget(klucz2, 0777 | IPC_CREAT);

  wyswietl_naglowek_serwera();
  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");

  while(1)
  {
    if(msgrcv(input, &kolor, sizeof(int)*100, 0, 0) == -1)
    {
      printf("[ERROR]: Odbiór koloru od klienta nie powiódł się!\n");
      exit(1);
    }

    printf("--------------------------------------------------\n");
    printf("[kolor_serwera_przed]: RGB(%3d %3d %3d)\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue);
    printf("[kolor_klienta]:       RGB(%3d %3d %3d) PID[%ld]\n", kolor.red, kolor.green, kolor.blue, kolor.pID);

    przed_i_po.kolor_przed = kolor_na_serwerze;
    kolor_na_serwerze = zmieszaj(kolor.red, kolor.green, kolor.blue, kolor, kolor_na_serwerze);
    printf("[kolor_serwera_po]:    RGB(%3d %3d %3d)\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue);

    przed_i_po.kolor_po = kolor_na_serwerze;
    przed_i_po.pID = getpid();

    // if(msgsnd(output, &przed_i_po, sizeof(int)*100, 0) == -1)
    // {
    //    printf("[ERROR]: Wysyłanie koloru do klienta nie powiodło się!\n");
    //    exit(1);
    // }
   }
   return 0;
}
