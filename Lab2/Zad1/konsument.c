#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void header()
{
  puts("  ┬┌─┌─┐┌┐┌┌─┐┬ ┬┌┬┐┌─┐┌┐┌┌┬┐");
  puts("  ├┴┐│ ││││└─┐│ ││││├┤ │││ │ ");
  puts("  ┴ ┴└─┘┘└┘└─┘└─┘┴ ┴└─┘┘└┘ ┴ ");
}

void makeLine()
{
  puts("  ------------------------------------------");
}

void introduction()
{
  header();
  makeLine();
  puts("  Tekst będzie odbierany linijka po linijce,");
  puts("  w momencie, w którym producent zatwierdzi");
  puts("  linijkę naciśnięciem klawisze ENTER.");
}

void beginning()
{
  system("clear");
	puts("");
  introduction();
	puts("");
}

void ending()
{
  makeLine();
	puts("");
}

int main (void)
{
  beginning();

  puts("  ODBIERANY TEKST:");
	puts("  ...");
  //...

  ending();
	return 0;
}
