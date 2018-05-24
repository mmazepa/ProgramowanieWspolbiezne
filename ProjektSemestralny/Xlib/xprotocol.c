#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int new_window(int n, char* host)
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
  Status color;
  // Drawable drawable;

	display = XOpenDisplay(host);
	screen = DefaultScreen(display);
	visual = DefaultVisual(display, screen);
	depth = DefaultDepth(display, screen);
  colormap = DefaultColormap(display, screen);

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
        color = XParseColor(display, colormap, "red", &xcolor);
        // printf("1[%d]\n", color);
        XSetForeground(display, gc, xcolor.red*color);
				XFillRectangle(display, window, gc, 100, 100, 300, 300);
        XFillRectangle(display, window, gc, 0, 0, 100, 100);
        XFillRectangle(display, window, gc, 0, 400, 100, 100);
        XFillRectangle(display, window, gc, 400, 400, 100, 100);
        XFillRectangle(display, window, gc, 400, 0, 100, 100);
        // XDrawImageString(display, drawable, gc, 100, 100, "RGB(0,0,0)", 10);

				XFlush(display);
				break;
			case KeyPress:
				XCloseDisplay(display);
				exit(n);
		}
	}
}

int main(int argc, char *argv[])
{
    pid_t child_pid, wpid;
    int status = 0;
    int i;
    time_t start_time;
    time(&start_time);

    // system("clear");
    printf("\nX PROTOKÓŁ\n");
    printf("Oczekiwanie na zamknięcie wszystkich okien...\n");
    printf("------------------------------------------------------------------------------\n");

    for (i = 1; i < argc; i++)
    {
        if ((child_pid = fork()) == 0)
        {
            new_window(i, argv[i]);
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
      if (t == 1)
      {
        czas = "sekundzie";
      }
      else
      {
        czas = "sekundach";
      }
      printf("[PID: %5d] Okno graficzne nr %2d zamknięto po %2.f %s (%s).\n", (int)wpid, n, t, czas, argv[n]);
    }
    printf("------------------------------------------------------------------------------\n");
    printf("Wszystkie okna zostały zamknięte.\n\n");
    return 0;
}
