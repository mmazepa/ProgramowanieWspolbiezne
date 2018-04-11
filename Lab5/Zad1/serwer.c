#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define ROZMIAR_BAZY 50
#define MAX_LINE 20
// Plik z zawartoscią bazy
#define PLIK_BAZY "baza_danych"

// Struktura bazy
typedef struct Klient
{
	int id;
	char * nazwisko;
} Klient;

typedef struct Wiadomosc
{
	int id;
	char * homepath;
} Wiadomosc;

// Tworzenie i wypełnianie bazy
int stworz_baze_danych(void * data)
{
  FILE * fp;

  char buffer[MAX_LINE];
  int i = 0;

  if (fp = fopen(PLIK_BAZY, "r"))
  {
    // Wczytywanie z pliku do bazy
    while((fgets(buffer, sizeof(buffer), fp) != NULL) && (i<ROZMIAR_BAZY))
    {
      ((Klient *)data)[i].nazwisko = (char *) malloc(MAX_LINE);
      // Max. 20 znaków
      sscanf(buffer, "%d %20s", &((Klient *)data)[i].id, ((Klient *)data)[i].nazwisko);
      i++;
    }
    fclose(fp);
  }
  else
  {
    printf("Baza danych nie istnieje (plik nie istnieje)!");
    return 1;
  }
  return 0;
}

// Pobieranie nazwiska z bazy po ID
char * pobierz_nazwisko(void * data, int id)
{
  int i = 0;

  for (i = 0; i < ROZMIAR_BAZY; i++)
  {
    if(((Klient *)data)[i].id == id)
    {
      return ((Klient *)data)[i].nazwisko;
    }
  }
  return "Podane ID nie znajduje się w bazie danych!";
}

// Pobieranie woiadomości od klienta
Wiadomosc pobierz_dane_klienta(int client, int size)
{
  Wiadomosc data;

  unsigned char * buffer = (char *) malloc(size);

  read(client, buffer, size);

  memcpy(&data.id, buffer, sizeof(int));
  data.homepath = (char *) malloc(size - sizeof(int));
  memcpy(data.homepath, (buffer + sizeof(int)), size - sizeof(int));

	free(buffer);
	return data;
}

// Wysyłanie wiadomości (odpowiedzi) do klienta
void wyslij_wiadomosc(int serwer, void * db, void * data)
{
	int dlugosc = 0;
	unsigned char * wiadomosc;
  unsigned char * nazwisko = pobierz_nazwisko(db, ((Wiadomosc *)data)->id);

  wiadomosc = (char *) malloc(strlen(nazwisko) + sizeof(int) + 1);
  dlugosc = strlen(nazwisko);
  memcpy(wiadomosc, &dlugosc , sizeof(int));
  memcpy(wiadomosc + sizeof(int), nazwisko, dlugosc);

  write(serwer, wiadomosc, dlugosc + sizeof(int));

	free(wiadomosc);
}

int main()
{
	Klient dbdata[ROZMIAR_BAZY];
	Wiadomosc data;

	stworz_baze_danych(dbdata);

	mkfifo("klientfifo", 0666);
	mkfifo("serwerfifo", 0666);

	int klient = open("klientfifo", O_RDONLY);
	int serwer = open("serwerfifo", O_WRONLY);

	int dlugosc_wiadomosci = 0;
	int bytes = 0;

	while(1)
	{
    if((bytes = read(klient, &dlugosc_wiadomosci, sizeof(int))) > 0)
    {
      data = pobierz_dane_klienta(klient, dlugosc_wiadomosci);
      wyslij_wiadomosc(serwer, &dbdata, &data);
    }
  }

	close(klient);
	close(serwer);

	unlink("klientfifo");
	unlink("serwerfifo");
}
