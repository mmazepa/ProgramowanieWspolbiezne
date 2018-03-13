#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
  char tekst[1000] = "";
  int bufor = open("bufor.txt", O_RDWR);
  FILE *buforWrite = fopen("bufor.txt", "w");

  if(buforWrite)
  {
    char cz[1] = "";
    write(bufor, "Klient pisze: ", 14);
    fprintf(buforWrite, "%s", cz);
    fclose(buforWrite);
  }

  printf("Podaj tresc wiadomosci:\n");
  scanf("%s", tekst);
  write(bufor, tekst, 1000);

  close(bufor);
  while(open("lockfile", O_CREAT|O_EXCL, 0) == -1)
  {
    printf("Serwer zajęty, proszę czekać...\n");
    sleep(3);
  }

    FILE *buforRead  = fopen("bufor.txt", "r");
    if(buforRead)
    {
      char slowo[100];
      char c;

      while((c = fscanf(buforRead, "%s", slowo)) != EOF)
      {
        printf("%s", slowo);
      }
      printf("\n");
      fclose(buforRead);
    }
    else printf("Podczas próby odczyania zawartości bufora wystąpił błąd.\n");

  return 0;
}
