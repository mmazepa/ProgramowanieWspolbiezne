#include <X11/Xlib.h>
#include <X11/X.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "funkcje.h"

#define true 0
#define false 1

int isValidNumber(char *string)
{
  int i;
  for (i = 0; i < strlen(string); i++)
  {
    if (string[i] < 48 || string[i] > 57)
    return false;
  }
  return true;
}

int areNumbersValid(char *str1, char *str2, char *str3)
{
  if (isValidNumber(str1) == false) return false;
  if (isValidNumber(str2) == false) return false;
  if (isValidNumber(str3) == false) return false;
  return true;
}

XColor przygotuj_xcolor(int red, int green, int blue)
{
  XColor newColor;
  newColor.red = (red * 65535)/257;
  newColor.green = (green * 65535)/257;
  newColor.blue = (blue * 65535)/257;
  return newColor;
}

int new_window(int n, char* host, Kolor kolor)
{
	Display *display;
	Window window;
	XSetWindowAttributes window_attributes;
	GC gc;
	Visual *visual;
	int depth;
	int screen;
	XEvent event;
  XColor xcolor;
  Colormap colormap;
  // Status color;
  Drawable drawable;

	display = XOpenDisplay(host);
	screen = DefaultScreen(display);
	visual = DefaultVisual(display, screen);
	depth = DefaultDepth(display, screen);
  colormap = DefaultColormap(display, screen);

  xcolor = przygotuj_xcolor(kolor.red, kolor.green, kolor.blue);

	window_attributes.background_pixel = XWhitePixel(display,screen);
	window_attributes.override_redirect = False;

	window = XCreateWindow(
    display,
    XRootWindow(display, screen),
    100, 100, 500, 500, 10,
    depth, InputOutput, visual,
    CWBackPixel|CWOverrideRedirect,
    &window_attributes
  );
	XSelectInput(display,window,ExposureMask|KeyPressMask);
	XMapWindow(display,window);
	gc = DefaultGC(display,screen);

	while (1)
  {
		XNextEvent(display,&event);
		switch (event.type)
    {
			case Expose:
        XAllocColor(display, DefaultColormap(display, 0), &xcolor);

        XSetForeground(display, gc, 0);
        XFillRectangle(display, window, gc, 100, 100, 300, 300);


        XColor bialy = przygotuj_xcolor(255, 255, 255);
        XAllocColor(display, DefaultColormap(display, 0), &bialy);
        XSetForeground(display, gc, bialy.pixel);
				XFillRectangle(display, window, gc, 110, 110, 280, 280);

        XSetForeground(display, gc, xcolor.pixel);
				XFillRectangle(display, window, gc, 120, 120, 260, 260);
        XFillRectangle(display, window, gc, 0, 0, 100, 100);
        XFillRectangle(display, window, gc, 0, 400, 100, 100);
        XFillRectangle(display, window, gc, 400, 400, 100, 100);
        XFillRectangle(display, window, gc, 400, 0, 100, 100);

        char *colorText = malloc(sizeof(char)*32);
        sprintf(colorText, "Aktualny kolor: RGB(%3d %3d %3d)", kolor.red, kolor.green, kolor.blue);

        drawable = window;
        XColor czarny = przygotuj_xcolor(0, 0, 0);
        XAllocColor(display, DefaultColormap(display, 0), &czarny);
        XSetForeground(display, gc, 0);

        Font font = XLoadFont(display, "-*-fixed-*-*-*-18-*-*-*-*-*-*-*");
        XSetFont(display, gc, font);
        XDrawString(display, drawable, gc, 110, 80, colorText, sizeof(char)*32);

				XFlush(display);
				break;
			case KeyPress:
				XCloseDisplay(display);
				exit(n);
		}
	}
}

Kolor przygotuj_kolor(char *argv[])
{
  int kolor_red, kolor_green, kolor_blue;
  Kolor kolor;

  if(!argv[1] || !argv[2] || !argv[3] || argv[4])
  {
    fail("Niepoprawna ilość argumentów, powinny być dokładnie 3!");
  }

  if (areNumbersValid(argv[1], argv[2], argv[3]) != 0)
  {
    fail("Argumenty powinny być liczbami naturalnymi!");
  }

  kolor_red = atoi(argv[1]);
  kolor_green = atoi(argv[2]);
  kolor_blue = atoi(argv[3]);

  if (kolor_red < 0 || kolor_green < 0 || kolor_blue < 0)
  {
    fail("Argumenty powinny być większe lub równe 0!");
  }

  if (kolor_red > 255 || kolor_green > 255 || kolor_blue > 255)
  {
    fail("Argumenty powinny być mniejsze lub równe 255!");
  }

  kolor.red = kolor_red;
  kolor.green = kolor_green;
  kolor.blue = kolor_blue;
  kolor.pID = getpid();

  return kolor;
}

int main(int argc, char *argv[])
{
  Kolor kolor, kolor2;
  Przed_i_po przed_i_po;

  int input, output;

  int kolor_red = 0;
  int kolor_green = 0;
  int kolor_blue = 0;

  input = msgget(klucz1, 0777);
  output = msgget(klucz2, 0777);

  // wyswietl_naglowek("klient");
  // printf("--------------------------------------------------\n");

  kolor = przygotuj_kolor(argv);

  if(msgsnd(input, &kolor, sizeof(Kolor)*10, 0) == -1)
  {
    fail("Wysyłanie koloru do serwera nie powiodło się!");
  }

  if(msgrcv(output, &kolor2, sizeof(Kolor)*10, 0, 0) == -1)
  {
    fail("Odbieranie koloru od serwera nie powiodło się!");
  }

  printf("[podany_kolor]:  RGB(%3d %3d %3d)\n", kolor.red, kolor.green, kolor.blue);
  printf("[kolor_serwera]: RGB(%3d %3d %3d)\n", kolor2.red, kolor2.green, kolor2.blue);

  new_window(0, ":0", kolor2);

  return 0;
}
