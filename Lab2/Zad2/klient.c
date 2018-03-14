#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define ROZMIAR_BUFORA 512
#define TRUE 1

// NAWIĄZANIE POŁĄCZENIA Z SERWEREM
void connect()
{
	while (open("lockfile",O_CREAT|O_EXCL, 0711)==-1)
  {
    printf("Serwer zajęty, proszę czekać!\n");
    sleep(3);
  }
}

// WYSYŁANIE WIADOMOŚCI DO SERWERA
void sendMessage()
{
	int dane;
	char bufor[ROZMIAR_BUFORA];
	char znak[1];
	int licznik = 0;

	char nazwa_uzytkownika[100];
	getlogin_r(nazwa_uzytkownika, 100);
	char output[1024];

	while((dane = open("dane.txt", O_RDWR|O_CREAT|O_APPEND, 0711)) < 0) {}

	if(dane != 0)
	{
		printf("\n%s:\n", nazwa_uzytkownika);
		while(TRUE)
		{
			read(0,znak,1);
			if(znak[0] == 27)
      {
				licznik = sprintf(output, "%s:\n%s", nazwa_uzytkownika, bufor);
				write(dane, output, licznik);
				break;
			}
			bufor[licznik] = znak[0];
			licznik++;
		}
	}
}

// ODEBRANIE WIADOMOŚCI ZWROTNEJ OD SERWERA
void getMessage()
{
	int wyniki;
	char bufor[ROZMIAR_BUFORA];

	while((wyniki = open("wyniki.txt", O_RDWR)) < 0) {}

	if(wyniki != 0)
	{
		while(read(wyniki,bufor,ROZMIAR_BUFORA) < 1) {}
		printf("SERWER WYSŁAŁ WIADOMOŚĆ:\n%s", bufor);
		close(wyniki);
	}
}

// OCZYSZCZANIE BUFORÓW
void disconnect()
{
	unlink("wyniki.txt");
}

// NAGŁÓWEK DLA KLIENTA
void header(char nazwa_uzytkownika[100])
{
  printf("\n");
  printf("┬┌─┬  ┬┌─┐┌┐┌┌┬┐\n");
  printf("├┴┐│  │├┤ │││ │ \n");
  printf("┴ ┴┴─┘┴└─┘┘└┘ ┴ \n");
  printf("Wyślij wiadomość do serwera i czekaj na odpowiedź.");
  printf("\n");
	printf("UŻYTKOWNIK: %s\n", nazwa_uzytkownika);
}

// FUNKCJA GŁÓWNA
int main(int argc, char *argv[])
{
	char nazwa_uzytkownika[100];
	getlogin_r(nazwa_uzytkownika, 100);

  header(nazwa_uzytkownika);
	connect();
	sendMessage();
	getMessage();
	disconnect();

  getchar();
  return 0;
}
