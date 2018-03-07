#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void header()
{
  puts("  ┌─┐┬─┐┌─┐┌┬┐┬ ┬┌─┐┌─┐┌┐┌┌┬┐");
  puts("  ├─┘├┬┘│ │ │││ ││  ├┤ │││ │ ");
  puts("  ┴  ┴└─└─┘─┴┘└─┘└─┘└─┘┘└┘ ┴ ");
}

void makeLine()
{
  puts("  ------------------------------------------");
}

void introduction()
{
  header();
  makeLine();
  puts("  Wpisz tekst, linijki zatwierdzaj ENTER'em,");
	puts("  zakończ przekaz klawiszem ESC.");
}

void beginning()
{
  system("clear");
	puts("");
  introduction();
	puts("");
}

int main (void)
{
  beginning();

	puts("  TWÓJ TEKST: ");
	printf("  ");

  char string;
  scanf("%s" , &string);

  printf("\n  WPISANO:\n  %s\n", &string);

  makeLine();
	puts("");
	return 0;
}
