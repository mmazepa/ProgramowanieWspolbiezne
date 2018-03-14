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
	int counter = 0;

	char uzytkownik[100];
	getlogin_r(uzytkownik, 100);
	char output[1024];

	while((dane = open("dane.txt", O_RDWR|O_CREAT|O_APPEND, 0711)) < 0) {}

	if(dane != 0)
	{
		printf("\n%s:\n", uzytkownik);
		while(TRUE)
		{
			read(0,znak,1);
			if(znak[0] == 27)
      {
				counter = sprintf(output, "%s:\n%s", uzytkownik, bufor);
				write(dane, output, counter);
				break;
			}
			bufor[counter] = znak[0];
			counter++;
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
		while(read(wyniki,bufor,512) < 1) {}
		printf("\nSERWER WYSŁAŁ WIADOMOŚĆ:\n%s", bufor);
		close(wyniki);
	}
}

// OCZYSZCZANIE BUFORÓW
void disconnect()
{
	unlink("wyniki.txt");
}

// FUNKCJA GŁÓWNA
int main(int argc, char *argv[])
{
	char uzytkownik[100];
	getlogin_r(uzytkownik, 100);

  printf("\n");
  printf("┬┌─┬  ┬┌─┐┌┐┌┌┬┐\n");
  printf("├┴┐│  │├┤ │││ │ \n");
  printf("┴ ┴┴─┘┴└─┘┘└┘ ┴ \n");
  printf("\n");
	printf("TWOJA NAZWA: %s\n", uzytkownik);

	connect();
	sendMessage();
	getMessage();
	disconnect();

  getchar();
  return 0;
}
