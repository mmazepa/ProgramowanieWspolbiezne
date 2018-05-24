#include "funkcje.h"

void naglowek_serwera()
{
  system("clear");
  wyswietl_naglowek("serwer");
  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");
}

Kolor zmieszaj(int wartosc_red, int wartosc_green, int wartosc_blue, Kolor kolor_na_serwerze)
{
  Kolor kolor;

  if (kolor_na_serwerze.red == 254 && wartosc_red == 255)
    kolor.red = 255;
  else
    kolor.red = (kolor_na_serwerze.red + wartosc_red)/2;

  if (kolor_na_serwerze.green == 254 && wartosc_green == 255)
    kolor.green = 255;
  else
    kolor.green = (kolor_na_serwerze.green + wartosc_green)/2;

  if (kolor_na_serwerze.blue == 254 && wartosc_blue == 255)
    kolor.blue = 255;
  else
    kolor.blue = (kolor_na_serwerze.blue + wartosc_blue)/2;

  return kolor;
}

int main(int argc, char *argv[])
{
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

  naglowek_serwera();

  int licznik = 1;

  while(1)
  {
    if(msgrcv(input, &kolor, sizeof(Kolor)*10, 0, 0) == -1)
    {
      fail("Odbiór koloru od klienta nie powiódł się!");
    }

    printf("-----------------------------------------------------\n");
    printf("WIADOMOŚĆ NR %d\n",licznik);
    licznik++;
    printf("   [kolor_serwera_przed]: RGB(%3d %3d %3d)\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue);
    printf("   [kolor_klienta]:       RGB(%3d %3d %3d) PID[%ld]\n", kolor.red, kolor.green, kolor.blue, kolor.pID);

    przed_i_po.kolor_przed = kolor_na_serwerze;
    kolor_na_serwerze = zmieszaj(kolor.red, kolor.green, kolor.blue, kolor_na_serwerze);
    printf("   [kolor_serwera_po]:    RGB(%3d %3d %3d)\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue);

    przed_i_po.kolor_po = kolor_na_serwerze;
    przed_i_po.pID = getpid();

    // if(msgsnd(output, &przed_i_po, sizeof(Przed_i_po)*10, 0) == -1)
    // {
    //    fail("[ERROR]: Wysyłanie koloru do klienta nie powiodło się!");
    // }
   }
   return 0;
}
