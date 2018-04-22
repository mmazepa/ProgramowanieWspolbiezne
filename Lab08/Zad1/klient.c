#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#define ADRES_IP "153.19.1.202"
#define NUMER_PORTU 5000

// sprawdzenie, czy podano argument
// jeśli tak, zamiana na liczbę (int)
int zamien_na_liczbe(char *argument)
{
  int podana_liczba;
  if(argument)
  {
    podana_liczba = atoi(argument);
  }
  else
  {
    printf("[BŁĄD]: Nie podano argumentu!\n");
    exit(1);
  }
  return podana_liczba;
}

// obsługa komunikacji z serwerem
// wysłanie podanej liczby i odebranie wyniku
void komunikacja_z_serwerem(int wiadomosc)
{
  struct sockaddr_in ip4addr;
	bzero((char *) &ip4addr, sizeof(ip4addr));
	ip4addr.sin_family = AF_INET;
	ip4addr.sin_port = htons((ushort) NUMER_PORTU);
	inet_pton(AF_INET, ADRES_IP, &ip4addr.sin_addr);

	int fromlen;
	fromlen = sizeof(struct sockaddr_in);

	int s;
	s = socket(PF_INET, SOCK_DGRAM, 0);

	bind(s, (struct sockaddr*) &ip4addr, fromlen);

	int buff = htonl(wiadomosc);
	sendto(s, (char *)&buff, sizeof(buff), 0, (struct sockaddr*) &ip4addr, fromlen);

	printf("KLIENT -> SERWER: %d\n", wiadomosc);

	int byte_count;
	byte_count = recvfrom(s, (char *)&buff, sizeof(buff), 0, (struct sockaddr*) &ip4addr, &fromlen);
	buff = ntohl(buff);

	printf("SERWER -> KLIENT: %d\n", buff);
}

// odgadnięcie funkcji, którą oblicza serwer
// plus krótki dowód na to
void odgadniecie_funkcji(int liczba)
{
  printf("------------------------------------------\n");
  printf("Obliczana przez serwer funkcja to (x^2)+1.\n");
  int potega = (int)pow(liczba,2);
  printf("DOWÓD: %d^2 + 1 = %d + 1 = %d\n",liczba,potega,potega+1);
}

int main (int argc, char *argv[])
{
  int podana_liczba = zamien_na_liczbe(argv[1]);
  komunikacja_z_serwerem(podana_liczba);
  odgadniecie_funkcji(podana_liczba);
  return 0;
}
