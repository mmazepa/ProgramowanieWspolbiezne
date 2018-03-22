#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rozmiar_bazy 20
#define dlugosc_nazwiska 20

struct user
{
  int id;
  char* nazwisko;
};

struct kom_serv2cli
{
  int liczba;
  char* lancuch;
};

void wypelnij_baze(struct user baza_danych[rozmiar_bazy])
{
  strncpy(baza_danych[0].nazwisko, "Jedynkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[1].nazwisko, "Dwójkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[2].nazwisko, "Trójkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[3].nazwisko, "Czwórkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[4].nazwisko, "Piątkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[5].nazwisko, "Szóstkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[6].nazwisko, "Siódemkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[7].nazwisko, "Ósemkowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[8].nazwisko, "Dziewięciowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[9].nazwisko, "Dziesięciowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[10].nazwisko, "Aowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[11].nazwisko, "Beowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[12].nazwisko, "Ceowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[13].nazwisko, "Deowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[14].nazwisko, "Eowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[15].nazwisko, "Efowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[16].nazwisko, "Gieowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[17].nazwisko, "Haowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[18].nazwisko, "Iowski\0", dlugosc_nazwiska);
  strncpy(baza_danych[19].nazwisko, "Jotowski\0", dlugosc_nazwiska);
}

int main()
{
  // system("clear");
  printf("\n");
  printf("SERWER WITA!");
  printf("\n");

  // STWORZENIE BAZY DANYCH
  struct user baza_danych[rozmiar_bazy];

  // NADANIE ID I ZAREZERWOWANIE PAMIĘCI NA NAZWISKA
  for (int i = 0; i < rozmiar_bazy ; i++)
  {
    baza_danych[i].id = i+1;
    baza_danych[i].nazwisko = (char*)malloc(sizeof(char)*dlugosc_nazwiska);
  }

  // STATYCZNE WYPEŁNIENIE BAZY DANYCH
  wypelnij_baze(baza_danych);

  // WYPISANIE ZAWARTOŚCI BAZY W TERMINALU
  // for (int i = 0; i < rozmiar_bazy ; i++)
  // {
  //     printf("[%d]: %s\n", baza_danych[i].id, baza_danych[i].nazwisko);
  // }

  printf("\n");

  int podane_id = 0;
  int licznik = 0;
  printf("Podaj id: ");
  scanf("%d", &podane_id);

  // PRZESZUKIWANIE BAZY DANYCH
  for (int i = 0; i < rozmiar_bazy ; i++)
  {
    if(baza_danych[i].id == podane_id)
    {
      printf("[%d]: %s\n", baza_danych[i].id, baza_danych[i].nazwisko);
    }
    else
    {
      licznik++;
    }
  }

  if (licznik == rozmiar_bazy)
  {
    printf("Nie ma!\n");
  }

  printf("\n");
  return 0;
}
