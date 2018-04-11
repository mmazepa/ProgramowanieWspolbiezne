#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct Wiadomosc
{
  unsigned int dlugosc;
  int id;
  char * homepath;
} Wiadomosc;

// Pobieranie ID od użytkownika
int pobierz_id(char * wpis)
{
  int id = -1;

	if(wpis != NULL)
    sscanf(wpis, "%d", &id);
  else
    printf("Nie podano identyfikatora!\n");

	return id;
}

// Wysyłanie zapytania do serwera
void wyslij_wiadomosc(int klient, void * data)
{
  unsigned char * buffer;

  buffer = (char *) malloc(sizeof(int) + ((Wiadomosc *)data)->dlugosc);
  memcpy(buffer, &((Wiadomosc *)data)->dlugosc, sizeof(int));
  memcpy(buffer + sizeof(int), &((Wiadomosc *)data)->id, sizeof(int));
  memcpy(buffer + (2 * sizeof(int)), ((Wiadomosc *)data)->homepath, ((Wiadomosc *)data)->dlugosc - sizeof(int));

  write(klient, buffer, ((Wiadomosc *)data)->dlugosc + sizeof(int));

  free(buffer);
}

// Pobieranie danych z serwera
void pobierz_dane_serwera(int serwer)
{
  unsigned char * nazwisko;
  int dlugosc = 0;
  int bytes = 0;

	fsync(serwer);
	read(serwer, &dlugosc, sizeof(int));
	nazwisko = malloc(dlugosc);

	if((bytes=read(serwer, nazwisko, dlugosc)) > 0) { }
	printf("%s\n", nazwisko);
}

int main(int argc, char * argv[])
{
	Wiadomosc data;

	data.id = pobierz_id(argv[1]);
	data.homepath = getenv("HOME");
	data.dlugosc = sizeof(int) + strlen(data.homepath);

	if(data.id < 0)
	{
    printf("Identyfikator nie może być mniejszy od zera!\n");
		return 1;
	}

	int klient = open("klientfifo", O_WRONLY);
	int serwer = open("serwerfifo", O_RDONLY);

	wyslij_wiadomosc(klient, &data);
	pobierz_dane_serwera(serwer);
}
