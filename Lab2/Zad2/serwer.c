#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define ROZMIAR_BUFORA 512
#define TRUE 1

// ODEBRANIE WIADOMOŚCI OD KLIENTA
void getMessage()
{
   int dane = 0;
   char bufor[ROZMIAR_BUFORA];

   while((dane = open("dane.txt", O_RDWR)) < 0) {}

   if(dane != 0)
   {
     while(read(dane,bufor,512) < 1) {}
     printf("%s", bufor);
   }
}

// WYSYŁANIE WIADOMOŚCI ZWROTNEJ DO KLIENTA
void sendMessage()
{
	int wyniki;
	char bufor[ROZMIAR_BUFORA];
	char znak[1];
	int counter = 0;

	while((wyniki = open("wyniki.txt", O_RDWR|O_CREAT|O_EXCL, 0711)) < 0) {}

	if(wyniki != 0)
	{
		printf("SERWER - NAPISZ WIADOMOSC ZWROTNA DLA KLIENTA:\n");
		while(1)
		{
			read(0,znak,1);

			if(znak[0] == (char)27)
			{
				write(wyniki, bufor, counter);
				close(wyniki);
				break;
			}
			bufor[counter] = znak[0];
			counter++;
		}
	}
}

// OCZYSZCZANIE BUFORÓW
void disconnect()
{
		unlink("lockfile");
		unlink("dane.txt");
}

// FUNKCJA GŁÓWNA
int main()
{
	printf("KOMUNIKATOR TEKSTOWY - SERWER\n");

	while(TRUE)
	{
		getMessage();
		sendMessage();
		disconnect();
		printf("\n");
	}

	return 0;
}
