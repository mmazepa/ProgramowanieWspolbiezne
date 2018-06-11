#include <X11/Xlib.h>
#include <X11/X.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define true 0
#define false 1

typedef struct {
  long pID;
  int red;
  int green;
  int blue;
} Kolor;

typedef struct {
  Display *display;
	Window window;
	XSetWindowAttributes window_attributes;
	GC gc;
	Visual *visual;
	int depth;
	int screen;
	XEvent event;
  XColor xcolor;
  Drawable drawable;
} XlibWindow;

#define SHMSZ 27
Kolor kolor_na_serwerze = { .red = 0, .green = 0, .blue = 0 };

void wyswietl_naglowek()
{
  printf("           _                    _       _ _    \n");
  printf(" _ __ ___ (_) ___  ___ ______ _| |_ __ (_) | __\n");
  printf("| '_ ` _ \\| |/ _ \\/ __|_  / _` | | '_ \\| | |/ /\n");
  printf("| | | | | | |  __/\\__ \\/ / (_| | | | | | |   < \n");
  printf("|_| |_| |_|_|\\___||___/___\\__,_|_|_| |_|_|_|\\_\\\n");
}

void fail(char *error_message)
{
  printf("[ERROR]: %s\n", error_message);
  exit(1);
}

XColor przygotuj_xcolor(int red, int green, int blue)
{
  XColor newColor;
  newColor.red = (red * 65535)/257;
  newColor.green = (green * 65535)/257;
  newColor.blue = (blue * 65535)/257;
  return newColor;
}

void naglowek()
{
  system("clear");
  wyswietl_naglowek();
  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");
  printf("-----------------------------------------------------\n");
}

int miks(int kolor1_rgb, int kolo2_rgb)
{
  int mieszany_kolor;
  mieszany_kolor = (kolor1_rgb + kolo2_rgb)/2;

  if (kolor1_rgb + 1 == kolo2_rgb)
  {
    mieszany_kolor = mieszany_kolor + 1;
  }

  return mieszany_kolor;
}

Kolor zmieszaj(Kolor kolor1, Kolor kolor2)
{
  Kolor kolor;

  kolor.red = miks(kolor1.red, kolor2.red);
  kolor.green = miks(kolor1.green, kolor2.green);
  kolor.blue = miks(kolor1.blue, kolor2.blue);

  return kolor;
}

int new_window(int n, char* host, Kolor kolor, char* s)
{
  XlibWindow xlibwindow;

	xlibwindow.display = XOpenDisplay(host);
	xlibwindow.screen = DefaultScreen(xlibwindow.display);
	xlibwindow.visual = DefaultVisual(xlibwindow.display, xlibwindow.screen);
	xlibwindow.depth = DefaultDepth(xlibwindow.display, xlibwindow.screen);

  xlibwindow.xcolor = przygotuj_xcolor(kolor.red, kolor.green, kolor.blue);

	xlibwindow.window_attributes.background_pixel = XWhitePixel(xlibwindow.display, xlibwindow.screen);
	xlibwindow.window_attributes.override_redirect = False;

	xlibwindow.window = XCreateWindow(
    xlibwindow.display,
    XRootWindow(xlibwindow.display, xlibwindow.screen),
    100, 100, 500, 500, 10,
    xlibwindow.depth, InputOutput, xlibwindow.visual,
    CWBackPixel|CWOverrideRedirect,
    &xlibwindow.window_attributes
  );
  XStoreName(xlibwindow.display, xlibwindow.window, "Color Mixer 2018");
	XSelectInput(xlibwindow.display, xlibwindow.window, ExposureMask|KeyPressMask);
	XMapWindow(xlibwindow.display, xlibwindow.window);
	xlibwindow.gc = DefaultGC(xlibwindow.display, xlibwindow.screen);

  XColor bialy = przygotuj_xcolor(255, 255, 255);
  XAllocColor(xlibwindow.display, DefaultColormap(xlibwindow.display, 0), &bialy);

  XColor czarny = przygotuj_xcolor(0, 0, 0);
  XAllocColor(xlibwindow.display, DefaultColormap(xlibwindow.display, 0), &czarny);

	while (1)
  {
    char getRed[3], getGreen[3], getBlue[3];
    int counter = 0;

    for(counter = 4; counter <= 6; counter++) getRed[counter-4] = s[counter];
    for(counter = 8; counter <= 11; counter++) getGreen[counter-8] = s[counter];
    for(counter = 12; counter <= 14; counter++) getBlue[counter-12] = s[counter];

    int numRed, numGreen, numBlue;
    numRed = atoi(getRed);
    numGreen = atoi(getGreen);
    numBlue = atoi(getBlue);

    printf("RGB(%3d %3d %3d)\n", numRed, numGreen, numBlue);

    kolor.red = numRed;
    kolor.green = numGreen;
    kolor.blue = numBlue;

    kolor_na_serwerze = kolor;

    xlibwindow.xcolor = przygotuj_xcolor(kolor.red, kolor.green, kolor.blue);

		XNextEvent(xlibwindow.display, &xlibwindow.event);
		switch (xlibwindow.event.type)
    {
			case Expose:
        XAllocColor(xlibwindow.display, DefaultColormap(xlibwindow.display, 0), &xlibwindow.xcolor);

        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 0, 0, 500, 500);

        XSetForeground(xlibwindow.display, xlibwindow.gc, bialy.pixel);
				XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 10, 10, 480, 480);

        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 100, 100, 300, 300);

        XSetForeground(xlibwindow.display, xlibwindow.gc, bialy.pixel);
				XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 110, 110, 280, 280);

        XSetForeground(xlibwindow.display, xlibwindow.gc, xlibwindow.xcolor.pixel);
				XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 120, 120, 260, 260);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 10, 10, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 10, 400, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 400, 400, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 400, 10, 90, 90);

        char *colorText = malloc(sizeof(char)*32);
        sprintf(colorText, "Aktualny kolor: RGB(%3d %3d %3d)", kolor.red, kolor.green, kolor.blue);

        xlibwindow.drawable = xlibwindow.window;
        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);

        Font font = XLoadFont(xlibwindow.display, "-*-fixed-*-*-*-18-*-*-*-*-*-*-*");
        XSetFont(xlibwindow.display, xlibwindow.gc, font);
        XDrawString(xlibwindow.display, xlibwindow.drawable, xlibwindow.gc, 110, 80, colorText, sizeof(char)*32);

        // pierwsza opcja : podkreślenie pod 'R' w RGB
        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 288, 85, 30, 5);

				XFlush(xlibwindow.display);
				break;
			case KeyPress:
      {
        for(counter = 4; counter <= 6; counter++) getRed[counter-4] = s[counter];
        for(counter = 8; counter <= 11; counter++) getGreen[counter-8] = s[counter];
        for(counter = 12; counter <= 14; counter++) getBlue[counter-12] = s[counter];

        int numRed, numGreen, numBlue;
        numRed = atoi(getRed);
        numGreen = atoi(getGreen);
        numBlue = atoi(getBlue);

        kolor.red = numRed;
        kolor.green = numGreen;
        kolor.blue = numBlue;

        xlibwindow.xcolor = przygotuj_xcolor(kolor.red, kolor.green, kolor.blue);

        char my_key;
        if (!my_key)
        {
          my_key = 'r';
        }

        // printf("%ld\n", (long) XLookupKeysym (&event.xkey, 0));
        Kolor tmpKolor = { .red = 0, .green = 0, .blue = 0 };
        if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 114)  // R-key was pressed
        {
          // RGB(255,0,0)
          my_key = 'r';
          tmpKolor.red = 255;
          kolor = zmieszaj(kolor, tmpKolor);
        }
        else if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 103) // G-key was pressed
        {
          // RGB(0,255,0)
          my_key = 'g';
          tmpKolor.green = 255;
          kolor = zmieszaj(kolor, tmpKolor);
        }
        else if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 98) // B-key was pressed
        {
          // RGB(0,0,255)
          my_key = 'b';
          tmpKolor.blue = 255;
          kolor = zmieszaj(kolor, tmpKolor);
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65361) // Arrow-Left was pressed
        {
          switch (my_key)
          {
            case 'r':
              my_key = 'b';
              break;
            case 'g':
              my_key = 'r';
              break;
            case 'b':
              my_key = 'g';
              break;
          }
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65363) // Arrow-Right was pressed
        {
          switch (my_key)
          {
            case 'r':
              my_key = 'g';
              break;
            case 'g':
              my_key = 'b';
              break;
            case 'b':
              my_key = 'r';
              break;
          }
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65362) // Arrow-Up was pressed
        {
          switch (my_key)
          {
            case 'r':
              kolor.red++;
              break;
            case 'g':
              kolor.green++;
              break;
            case 'b':
              kolor.blue++;
              break;
          }
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65364) // Arrow-Down was pressed
        {
          switch (my_key)
          {
            case 'r':
              kolor.red--;
              if (kolor.red == -1) kolor.red = 255;
              break;
            case 'g':
              kolor.green--;
              if (kolor.green == -1) kolor.green = 255;
              break;
            case 'b':
              kolor.blue--;
              if (kolor.blue == -1) kolor.blue = 255;
              break;
          }
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65293
          || (long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65307) // Enter or ESC was pressed
        {
          XCloseDisplay(xlibwindow.display);
          exit(n);
        }

        kolor.red = abs(kolor.red%256);
        kolor.green = abs(kolor.green%256);
        kolor.blue = abs(kolor.blue%256);

        sprintf(colorText, "Aktualny kolor: RGB(%3d %3d %3d)", kolor.red, kolor.green, kolor.blue);
        sprintf(s, "RGB(%3d %3d %3d)", kolor.red, kolor.green, kolor.blue);

        XSetForeground(xlibwindow.display, xlibwindow.gc, bialy.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 100, 10, 300, 90);
        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);

        XDrawString(xlibwindow.display, xlibwindow.drawable, xlibwindow.gc, 110, 80, colorText, sizeof(char)*32);

        xlibwindow.xcolor = przygotuj_xcolor(kolor.red, kolor.green, kolor.blue);
        XAllocColor(xlibwindow.display, DefaultColormap(xlibwindow.display, 0), &xlibwindow.xcolor);
        XSetForeground(xlibwindow.display, xlibwindow.gc, xlibwindow.xcolor.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 120, 120, 260, 260);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 10, 10, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 10, 400, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 400, 400, 90, 90);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 400, 10, 90, 90);

        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);
        if(my_key == 'r')
        {
          XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 288, 85, 30, 5);
        }
        else if(my_key == 'g')
        {
          XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 325, 85, 30, 5);
        }
        else if(my_key == 'b')
        {
          XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 360, 85, 30, 5);
        }
        break;
      }
		}
	}
}

int main(int argc, char *argv[])
{
  int shmid;
  key_t key;
  char *shm, *s;

  key = 5678;

  if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
      perror("shmget");
      fail("shmget");
  }

  if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
      perror("shmat");
      fail("shmat");
  }

  s = shm;

  naglowek();
  if (argc <= 1) fail("Podaj co najmniej jeden 'adres_ip:ekran'.");

  pid_t child_pid, wpid;
  int status = 0;
  int i;
  time_t start_time;
  time(&start_time);

  printf("\nX PROTOKÓŁ: Oczekiwanie na zamknięcie wszystkich okien...\n");
  printf("------------------------------------------------------------------------------\n");

  for (i = 1; i < argc; i++)
  {
      if ((child_pid = fork()) == 0)
      {
          new_window(i, argv[i], kolor_na_serwerze, s);
          exit(0);
      }
  }

  while ((wpid = wait(&status)) > 0)
  {
    int n = status >> 8;
    time_t end_time;
    time(&end_time);
    double t = difftime(end_time, start_time);
    char *czas;

    if (t == 1) czas = "sekundzie";
    else czas = "sekundach";

    printf("[PID: %5d] Okno graficzne nr %2d zamknięto po %2.f %s (%s).\n", (int)wpid, n, t, czas, argv[n]);
  }

  printf("------------------------------------------------------------------------------\n");
  printf("Wszystkie okna zostały zamknięte.\n\n");

  return 0;
}
