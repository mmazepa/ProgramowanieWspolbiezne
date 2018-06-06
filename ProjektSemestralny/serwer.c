#include "funkcje.h"

void naglowek_serwera()
{
  system("clear");
  wyswietl_naglowek("serwer");
  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");
  printf("-----------------------------------------------------\n");
}

int miks(int serwer_kolor, int klient_kolor)
{
  int mieszany_kolor;
  mieszany_kolor = (serwer_kolor + klient_kolor)/2;

  if (serwer_kolor + 1 == klient_kolor)
  {
    mieszany_kolor = mieszany_kolor + 1;
  }

  return mieszany_kolor;
}

Kolor zmieszaj(int wartosc_red, int wartosc_green, int wartosc_blue, Kolor kolor_na_serwerze)
{
  Kolor kolor;

  kolor.red = miks(kolor_na_serwerze.red, wartosc_red);
  kolor.green = miks(kolor_na_serwerze.green, wartosc_green);
  kolor.blue = miks(kolor_na_serwerze.blue, wartosc_blue);

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

  naglowek_serwera();

  int licznik = 1;

  while(1)
  {
    input = msgget(klucz1, 0777 | IPC_CREAT);
    output = msgget(klucz2, 0777 | IPC_CREAT);

    if(msgrcv(input, &kolor, sizeof(Kolor)*10, 0, 0) == -1)
    {
      fail("Odbiór koloru od klienta nie powiódł się!");
    }

    printf("[%d]: mix RGB(%3d %3d %3d) & RGB(%3d %3d %3d) -> ", licznik, kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue, kolor.red, kolor.green, kolor.blue);
    kolor_na_serwerze = zmieszaj(kolor.red, kolor.green, kolor.blue, kolor_na_serwerze);
    printf("RGB(%3d %3d %3d) [%ld]\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue, kolor.pID);

    if(msgsnd(output, &kolor_na_serwerze, sizeof(Kolor)*10, 0) == -1)
    {
       fail("[ERROR]: Wysyłanie koloru do klienta nie powiodło się!");
    }

    msgctl(input, IPC_RMID, 0);
    msgctl(output, IPC_RMID, 0);
    licznik++;
   }

   return 0;
}
