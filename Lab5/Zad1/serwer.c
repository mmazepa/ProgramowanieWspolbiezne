#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define DB_SIZE 20
#define MAX_LINE 100
#define DB_DATA_FILE "baza"  //plik z zawartoscia bazy danych

//Struktura bazy danych

typedef struct _CLIENT_DATA
{
	int id;
	char * nazwisko;
} CLIENT_DATA;

typedef struct _MESSAGE_DATA
{
	int id;
	char * homepath;
} MESSAGE_DATA;

//Utworzenie bazy danych i uzupelnienie jej wartosciami

int utworzBaze(void * data)
{
  FILE * fp;

  char buffer[MAX_LINE];
  int i = 0;

  if (fp = fopen(DB_DATA_FILE, "r"))
  {
    while((fgets(buffer, sizeof(buffer), fp) != NULL) && (i<DB_SIZE))  // Zapis danych z pliku do bazy danych
    {
      ((CLIENT_DATA *)data)[i].nazwisko = (char *) malloc(MAX_LINE);
      sscanf(buffer, "%d %20s", &((CLIENT_DATA *)data)[i].id, ((CLIENT_DATA *)data)[i].nazwisko);   //20 znakow
      i++;
    }
    fclose(fp);
  }
  else
  {
    printf("Brak pliku z zawartoscia bazy danych!");
    return 1;
  }
  return 0;
}

//Pobieranie nazwiska z bazy przez ID rekordu

char * getNazwiskoByID(void * data, int id)
{
  int i = 0;

  for (i = 0; i < DB_SIZE; i++)
  {
    if(((CLIENT_DATA *)data)[i].id == id)
    {
      return ((CLIENT_DATA *)data)[i].nazwisko;
    }
  }
  return "Nie ma rekordu z takim podanym ID w bazie danych!";
}

//Pobieranie komunikatu od klienta do serwera (zapytanie)

MESSAGE_DATA getClientData(int client, int size)
{
  MESSAGE_DATA data;

  unsigned char * buffer = (char *) malloc(size);

  read(client, buffer, size);

  memcpy(&data.id, buffer, sizeof(int));
  data.homepath = (char *) malloc(size - sizeof(int));
  memcpy(data.homepath, (buffer + sizeof(int)), size - sizeof(int));

	free(buffer);
	return data;
}

//Wysylanie odpowiedzi (komunikatu) do klienta

void sendMessage(int server, void * db, void * data)
{
	int length = 0;
	unsigned char * message;
  unsigned char * nazwisko = getNazwiskoByID(db, ((MESSAGE_DATA *)data)->id);

  message = (char *) malloc(strlen(nazwisko) + sizeof(int) + 1);
  length = strlen(nazwisko);
  memcpy(message, &length , sizeof(int));
  memcpy(message + sizeof(int), nazwisko, length);

  write(server, message, length + sizeof(int));

	free(message);
}

//Glowna funkcja programu

int main()
{
	CLIENT_DATA dbdata[DB_SIZE];
	MESSAGE_DATA data;

	utworzBaze(dbdata);

	mkfifo("klientfifo", 0666);
	mkfifo("serwerfifo", 0666);

	int klient = open("klientfifo", O_RDONLY);
	int serwer = open("serwerfifo", O_WRONLY);

	int messageLength = 0;
	int bytes = 0;

	while(1)
	{
    if((bytes = read(klient, &messageLength, sizeof(int))) > 0)
    {
      data = getClientData(klient, messageLength);
      sendMessage(serwer, &dbdata, &data);
    }
  }

	close(klient);
	close(serwer);

	unlink("klientfifo");
	unlink("serwerfifo");
}
