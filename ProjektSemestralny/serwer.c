#include "funkcje.h"

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

#define ARRAY_SIZE 100
XlibWindow players[ARRAY_SIZE];

void naglowek_serwera()
{
  system("clear");
  wyswietl_naglowek("serwer");
  printf("Praca serwera w toku, oczekiwanie na zgłoszenia...\n");
  printf("-----------------------------------------------------\n");
}

int miks(int serwer_kolor, int klient_kolor)
{
  int mieszany_kolor;
  mieszany_kolor = (serwer_kolor + klient_kolor)/2;

  if (serwer_kolor + 1 == klient_kolor)
  {
    mieszany_kolor = mieszany_kolor + 1;
  }

  return mieszany_kolor;
}

Kolor zmieszaj(int wartosc_red, int wartosc_green, int wartosc_blue, Kolor kolor_na_serwerze)
{
  Kolor kolor;

  kolor.red = miks(kolor_na_serwerze.red, wartosc_red);
  kolor.green = miks(kolor_na_serwerze.green, wartosc_green);
  kolor.blue = miks(kolor_na_serwerze.blue, wartosc_blue);

  return kolor;
}

void updateDisplays()
{
  // int i;
  // for (i = 1; i <= 3; i++)
  // {
  //   // XDrawString(players[i].display, players[i].drawable, players[i].gc, 110, 80, "HEJKA!", sizeof(char)*32);
  //   printf("[%d_%d]: connCheck!\n", getpid(), i);
  // }
  // XDrawString(players[0].display, players[0].drawable, players[0].gc, 110, 80, "HEJKA!", sizeof(char)*32);
  // printf("[size: %ld]\n", sizeof(players));
}

int new_window(int n, char* host, Kolor kolor)
{
	// Display *display;
	// Window window;
	// XSetWindowAttributes window_attributes;
	// GC gc;
	// Visual *visual;
	// int depth;
	// int screen;
	// XEvent event;
  // XColor xcolor;
  // // Colormap colormap;
  // // Status color;
  // Drawable drawable;

  XlibWindow xlibwindow;

	xlibwindow.display = XOpenDisplay(host);

	xlibwindow.screen = DefaultScreen(xlibwindow.display);
	xlibwindow.visual = DefaultVisual(xlibwindow.display, xlibwindow.screen);
	xlibwindow.depth = DefaultDepth(xlibwindow.display, xlibwindow.screen);
  // colormap = DefaultColormap(display, screen);

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

  players[n] = xlibwindow;
  // printf("%d...\n", n);

	while (1)
  {
  	// XWarpPointer(display, window, window, 0, 0, 0, 0, 10, 10);
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

        // XEvent event;
        // XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
        // printf("mouse[%d,%d]\n", event.xbutton.x, event.xbutton.y);

				XFlush(xlibwindow.display);
				break;
			case KeyPress:
      {
        char my_key;
        if (!my_key)
        {
          my_key = 'r';
        }
        // printf("%ld\n", (long) XLookupKeysym (&event.xkey, 0));
        if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 114)  // R-key was pressed
        {
          // printf("[RED]:   RGB(255,0,0)\n");
          my_key = 'r';
          // --- TMP ---------------------------------------
          kolor.red = (kolor.red+255)/2;
          kolor.green = kolor.green/2;
          kolor.blue = kolor.blue/2;
          // --- TMP ---------------------------------------
        }
        else if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 103) // G-key was pressed
        {
          // printf("[GREEN]: RGB(0,255,0)\n");
          my_key = 'g';
          // --- TMP ---------------------------------------
          kolor.red = kolor.red/2;
          kolor.green = (kolor.green+255)/2;
          kolor.blue = kolor.blue/2;
          // --- TMP ---------------------------------------
        }
        else if ((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 98) // B-key was pressed
        {
          // printf("[BLUE]:  RGB(0,0,255)\n");
          my_key = 'b';
          // --- TMP ---------------------------------------
          kolor.red = kolor.red/2;
          kolor.green = kolor.green/2;
          kolor.blue = (kolor.blue+255)/2;
          // --- TMP ---------------------------------------
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
          // printf("arrow up!\n");
          // --- TMP ---------------------------------------
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
          // --- TMP ---------------------------------------
        }
        else if((long) XLookupKeysym (&xlibwindow.event.xkey, 0) == 65364) // Arrow-Down was pressed
        {
          // printf("arrow down!\n");
          // --- TMP ---------------------------------------
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
          // --- TMP ---------------------------------------
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
        // --- TMP ---------------------------------------
        sprintf(colorText, "Aktualny kolor: RGB(%3d %3d %3d)", kolor.red, kolor.green, kolor.blue);
        XSetForeground(xlibwindow.display, xlibwindow.gc, bialy.pixel);
        XFillRectangle(xlibwindow.display, xlibwindow.window, xlibwindow.gc, 100, 10, 300, 90);
        XSetForeground(xlibwindow.display, xlibwindow.gc, czarny.pixel);
        // int i;
        // for (i = 1; i <= sizeof(players); i++)
        // {
        //   XDrawString(players[i].display, players[i].drawable, players[i].gc, 110, 80, colorText, sizeof(char)*32);
        // }
        XDrawString(xlibwindow.display, xlibwindow.drawable, xlibwindow.gc, 110, 80, colorText, sizeof(char)*32);
        // --- TMP ---------------------------------------
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
        // --- TMP ---------------------------------------
        break;
      }
			case KeyRelease:
        // printf("released...\n");
        break;
		}
    updateDisplays();
	}
}

int main(int argc, char *argv[])
{
  Kolor kolor_na_serwerze;
  // Kolor kolor;

  int input, output;

  kolor_na_serwerze.red = 0;
  kolor_na_serwerze.green = 0;
  kolor_na_serwerze.blue = 0;
  kolor_na_serwerze.pID = getpid();

  naglowek_serwera();
  if (argc <= 1) fail("Podaj co najmniej jeden 'adres_ip:ekran'.");

  input = msgget(klucz1, 0777 | IPC_CREAT);
  output = msgget(klucz2, 0777 | IPC_CREAT);

  // int licznik = 1;
  //
  // while(1)
  // {
  //   // if(msgrcv(input, &kolor, sizeof(Kolor)*10, 0, 0) == -1)
  //   // {
  //   //   fail("Odbiór koloru od klienta nie powiódł się!");
  //   // }
  //
  //   // new_window(0, ":0", kolor_na_serwerze);
  //
  //   printf("[%d]: mix RGB(%3d %3d %3d) & RGB(%3d %3d %3d) -> ", licznik, kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue, kolor.red, kolor.green, kolor.blue);
  //   kolor_na_serwerze = zmieszaj(kolor.red, kolor.green, kolor.blue, kolor_na_serwerze);
  //   printf("RGB(%3d %3d %3d) [%ld]\n", kolor_na_serwerze.red, kolor_na_serwerze.green, kolor_na_serwerze.blue, kolor.pID);
  //
  //   // if(msgsnd(output, &kolor_na_serwerze, sizeof(Kolor)*10, 0) == -1)
  //   // {
  //   //    fail("[ERROR]: Wysyłanie koloru do klienta nie powiodło się!");
  //   // }
  //
  //   licznik++;
  //  }

  // TMP TMP TMP --------------------------
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
          new_window(i, argv[i], kolor_na_serwerze);
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
  // TMP TMP TMP --------------------------

  msgctl(input, IPC_RMID, 0);
  msgctl(output, IPC_RMID, 0);

  return 0;
}
