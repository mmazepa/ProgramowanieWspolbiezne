#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct _MESSAGE_INFO
{
  unsigned int length;
  int id;
  char * homepath;
} MESSAGE_INFO;

//Pobieranie z klawiatury ID do zapytania

int getID(char * arg)
{
  int id = -1;

	if(arg != NULL)
    sscanf(arg, "%d", &id);
  else
    printf("Nie podano ID rekordu!\n");

	return id;
}

//Wysylanie zapytania do serwera

void sendMessage(int klient, void * data)
{
  unsigned char * buffer;

  buffer = (char *) malloc(sizeof(int) + ((MESSAGE_INFO *)data)->length);
  memcpy(buffer, &((MESSAGE_INFO *)data)->length, sizeof(int));
  memcpy(buffer + sizeof(int), &((MESSAGE_INFO *)data)->id, sizeof(int));
  memcpy(buffer + (2 * sizeof(int)), ((MESSAGE_INFO *)data)->homepath, ((MESSAGE_INFO *)data)->length - sizeof(int));

  write(klient, buffer, ((MESSAGE_INFO *)data)->length + sizeof(int));

  free(buffer);
}

//Pobieranie danych z serwera

void getServerData(int serwer)
{
  unsigned char * nazwisko;
  int length = 0;
  int bytes = 0;

	fsync(serwer);
	read(serwer, &length, sizeof(int));
	nazwisko = malloc(length);

	if((bytes=read(serwer, nazwisko, length)) > 0) { }
	printf("%s\n", nazwisko);
}

//Glowna funkcja programu

int main(int argc, char * argv[])
{
	MESSAGE_INFO data;

	data.id = getID(argv[1]);
	data.homepath = getenv("HOME");
	data.length = sizeof(int) + strlen(data.homepath);

	if(data.id < 0)
	{
		return 1;
	}

	int klient = open("klientfifo", O_WRONLY);
	int serwer = open("serwerfifo", O_RDONLY);

	sendMessage(klient, &data);
	getServerData(serwer);
}
