#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int startNewWindow(int n, char* host)
{
	Display *mydisplay;
	Window mywindow;
	XSetWindowAttributes mywindowattributes;
	// XGCValues mygcvalues;
	GC mygc;
	Visual *myvisual;
	int mydepth;
	int myscreen;
	// Colormap mycolormap;
	XEvent myevent;

	mydisplay = XOpenDisplay(host);

	myscreen = DefaultScreen(mydisplay);
	myvisual = DefaultVisual(mydisplay,myscreen);
	mydepth = DefaultDepth(mydisplay,myscreen);

	mywindowattributes.background_pixel = XWhitePixel(mydisplay,myscreen);
	mywindowattributes.override_redirect = False;

	mywindow = XCreateWindow(mydisplay, XRootWindow(mydisplay, myscreen), 100, 100, 500, 500, 10, mydepth, InputOutput, myvisual, CWBackPixel|CWOverrideRedirect, &mywindowattributes);

	XSelectInput(mydisplay,mywindow,ExposureMask|KeyPressMask);

	// mycolormap = DefaultColormap(mydisplay,myscreen);

	XMapWindow(mydisplay,mywindow);

	mygc = DefaultGC(mydisplay,myscreen);

	int i, j;

	while (1)
  {
		XNextEvent(mydisplay,&myevent);

		switch (myevent.type)
    {
			case Expose:
				for (i = 0; i < 16; i++)
        {
					for (j = 0; j < 16; j++)
          {
						XSetForeground(mydisplay, mygc, 500*i+10*j);
						XFillRectangle(mydisplay, mywindow, mygc, 20*i +n, 20*j +n, 20*(i+1), 20*(j+1));
						XFlush(mydisplay);
					}
				}
				break;
			 case KeyPress:
				XCloseDisplay(mydisplay);
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

    for(i = 1; i < argc; i++)
    {
        if ((child_pid = fork()) == 0)
        {
            startNewWindow(i, argv[i]);
            exit(0);
        }
    }

	while ((wpid = wait(&status)) > 0)
  {
		int n = status >> 8;
		time_t end_time;
		time(&end_time);
		double t = difftime(end_time, start_time);
		printf("Okno graficzne (pid: %d) numer %d z %s zostalo zamkniete po %.f sekundach\n", (int)wpid, n, argv[n], t);
	}
	return 0;
}
