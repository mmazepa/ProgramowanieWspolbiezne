#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in ip4addr;
	bzero((char *) &ip4addr, sizeof(ip4addr));
	ip4addr.sin_family = AF_INET;
	ip4addr.sin_port = htons((ushort) 5000);
	inet_pton(AF_INET, "153.19.1.202", &ip4addr.sin_addr);

	int fromlen;
	fromlen = sizeof(struct sockaddr_in);

	int msg;
	printf("Podaj liczbę: ");
	scanf("%d", &msg);

	int s;
	s = socket(PF_INET, SOCK_DGRAM, 0);

	bind(s, (struct sockaddr*) &ip4addr, fromlen);

	int buff = htonl(msg);
	sendto(s, (char *)&buff, sizeof(buff), 0, (struct sockaddr*) &ip4addr, fromlen);

	printf("KLIENT -> SERWER: %d\n", msg);

	int byte_count;
	byte_count = recvfrom(s, (char *)&buff, sizeof(buff), 0, (struct sockaddr*) &ip4addr, &fromlen);
	buff = ntohl(buff);

	printf("SERWER -> KLIENT: %d\n", buff);

  return 0;
}
