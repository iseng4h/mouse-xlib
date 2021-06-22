//
// Gerak mouse dan klik
// install paket xlib-dev
// # gcc -o mouse mouse.c -lX11
// ./mouse 10 10 1
//
// by Dhoto

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void mouseMove(int x, int y)
{
  Display *displayMain = XOpenDisplay(NULL);

  if(displayMain == NULL)
  {
    fprintf(stderr,"Error");
    exit(EXIT_FAILURE);
  }

  XWarpPointer(displayMain, None, None, 0,0,0,0, x, y);

  XCloseDisplay(displayMain);
}

void mouseClick(int button)
{
  Display *display = XOpenDisplay(NULL);
  XEvent event;
			
  if(display == NULL)
  {
    fprintf(stderr, "Errore nell'apertura del Display !!!\n");
    exit(EXIT_FAILURE);
  }
											
  memset(&event, 0x00, sizeof(event));

  event.type = ButtonPress;
  event.xbutton.button = button;
  event.xbutton.same_screen = True;
																	
  XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
																			
  event.xbutton.subwindow = event.xbutton.window;
																					
  while(event.xbutton.subwindow)
  {
    event.xbutton.window = event.xbutton.subwindow;

    XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
  }
																															
  if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
  
  XFlush(display);
  usleep(100000);
  
  event.type = ButtonRelease;
  event.xbutton.state = 0x100;
  
  if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Errore nell'invio dell'evento !!!\n");
  
  XFlush(display);
  
  XCloseDisplay(display);
}


int main(int argc, char** argv )
{

  mouseMove(atoi(argv[1]),atoi(argv[2]));
  mouseClick(atoi(argv[3]));
  
  return 0;
}
