#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Display *mydisplay;
Window mywindow;
XSetWindowAttributes mywindowattributes;
XGCValues mygcvalues;
GC mygc;
Visual *myvisual;
int mydepth;
int myscreen;
Colormap mycolormap;
XColor  mycolor,
        mycolor1,
        mycolor2,
        mycolor3,
        dummy;
XEvent myevent;

int main()
{
   mydisplay = XOpenDisplay("");
   myscreen = DefaultScreen(mydisplay);
   myvisual = DefaultVisual(mydisplay,myscreen);
   mydepth = DefaultDepth(mydisplay,myscreen);
   mywindowattributes.background_pixel = XWhitePixel(mydisplay,myscreen);
   mywindowattributes.override_redirect = False;

   mywindow = XCreateWindow(mydisplay,XRootWindow(mydisplay,myscreen),
                            100,100,500,500,10,mydepth,InputOutput,
                            myvisual,CWBackPixel|CWOverrideRedirect,
                            &mywindowattributes);

   XSelectInput(mydisplay,mywindow,ExposureMask|KeyPressMask);
   mycolormap = DefaultColormap(mydisplay,myscreen);
   XAllocNamedColor(mydisplay,mycolormap,"darkred",&mycolor,&dummy);
   XAllocNamedColor(mydisplay,mycolormap,"whitesmoke",&mycolor1,&dummy);
   XAllocNamedColor(mydisplay,mycolormap,"tomato",&mycolor2,&dummy);
   XAllocNamedColor(mydisplay,mycolormap,"black",&mycolor3,&dummy);
   XMapWindow(mydisplay,mywindow);
   mygc = DefaultGC(mydisplay,myscreen);

   while(1)
   {
      XNextEvent(mydisplay,&myevent);
      switch (myevent.type)
      {
         case Expose:
              XSetForeground(mydisplay,mygc,mycolor.pixel);
              XFillRectangle(mydisplay,mywindow,mygc,50,50,400,400);
              XSetForeground(mydisplay,mygc,mycolor1.pixel);
              XSetFunction(mydisplay,mygc,GXcopy);
              XSetLineAttributes(mydisplay,mygc,10,LineSolid,CapProjecting,JoinMiter);

              XDrawLine(mydisplay,mywindow,mygc,50,50,500,500);
              XDrawLine(mydisplay,mywindow,mygc,50,400,400,50);
              XDrawLine(mydisplay,mywindow,mygc,50,500,500,50);

              XSetForeground(mydisplay,mygc,mycolor2.pixel);
              XDrawLine(mydisplay,mywindow,mygc,55,55,250,445);
              XDrawLine(mydisplay,mywindow,mygc,55,55,445,250);
              XDrawLine(mydisplay,mywindow,mygc,250,445,445,250);

              XSetForeground(mydisplay,mygc,mycolor3.pixel);
              XDrawString(mydisplay,mywindow,mygc,50,30,"Hello there!",12);

              XFlush(mydisplay);
              break;
         case KeyPress:
              XCloseDisplay(mydisplay);
              exit(0);
      }
  }
}
