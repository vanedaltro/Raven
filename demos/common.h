#include <Raven.h>
#include <stdio.h>
#include <string.h>
static int demo_init(void){ RInitDesc d; memset(&d,0,sizeof d); d.backend=R_BACKEND_VULKAN; return Rinit_ex(&d); }
static Rid demo_caption(Rid parent, const char* text){ Rid l=Rwidget_add_child(parent,Rlabel_create(text)); Rlabel_set_text_size(l,15); return l; }
/* print a widget's centre in screen points */
static void demo_print_point(Rid win, Rid w, const char* name, float fx, float fy){
 int wx,wy; float x,y,ww,hh; Rwindow_get_position(win,&wx,&wy); Rwidget_get_rect(w,&x,&y,&ww,&hh);
 printf("POINT %s %.1f %.1f\n", name, wx+x+ww*fx, wy+y+hh*fy); fflush(stdout); }
static void demo_print_window(Rid win){ int x,y,w,h; Rwindow_get_position(win,&x,&y); Rwindow_get_size(win,&w,&h); printf("WINDOW %d %d %d %d\n",x,y,w,h); fflush(stdout);}
