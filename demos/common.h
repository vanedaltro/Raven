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
static Rid demo_box(Rid parent, float r, float g, float b, const char* text){
 Rid bx=Rwidget_add_child(parent,Rwidget_create(R_WIDGET_BORDER)); Rborder_set_background(bx,r,g,b,1);
 Rid l=Rwidget_add_child(bx,Rlabel_create(text)); Rlabel_set_text_size(l,15); Rslot_set_halign(l,R_HALIGN_CENTER); Rslot_set_valign(l,R_VALIGN_CENTER); return bx; }
static void demo_print_xy(Rid win, const char* name, float lx, float ly){ int wx,wy; Rwindow_get_position(win,&wx,&wy); printf("POINT %s %.1f %.1f\n",name,wx+lx,wy+ly); fflush(stdout);}
