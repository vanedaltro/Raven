#include "common.h"
static Rid make_split(Rid parent, RDirection dir, const char* title){
 Rid box=Rwidget_add_child(parent,Rwidget_create(R_WIDGET_VBOX)); Rslot_set_fill(box,1);
 demo_caption(box,title);
 Rid sp=Rwidget_add_child(box,Rwidget_create(R_WIDGET_SPLITTER)); Rslot_set_fill(sp,1);
 for(int i=0;i<2;i++){ Rid b=Rwidget_add_child(sp,Rwidget_create(R_WIDGET_BORDER));
  if(i) Rborder_set_background(b,.20f,.45f,.85f,1); else Rborder_set_background(b,.85f,.45f,.20f,1);
  Rid l=Rwidget_add_child(b,Rlabel_create(i?"pane 2":"pane 1")); Rslot_set_halign(l,R_HALIGN_CENTER); Rslot_set_valign(l,R_VALIGN_CENTER);}
 Rwidget_set_direction(sp,dir); return sp; }
int main(void){
 if(!demo_init()) return 1;
 Rid win=Rwindow_create("Splitter: LTR vs RTL",640,420,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,10); Rwindow_set_content(win,root);
 Rid a=make_split(root,R_DIRECTION_LTR,"Left-to-right splitter: drag the gap between the panes");
 Rid b=make_split(root,R_DIRECTION_RTL,"Right-to-left splitter (same code + Rwidget_set_direction RTL)");
 int printed=0;
 while(Rwait_frame(0.05)){ if(!printed++ ){ for(int k=0;k<5;k++) Rdraw_frame(); demo_print_window(win);
   Rid p; float x,y,w,h;
   p=Rwidget_get_child(a,0); demo_print_point(win,p,"ltr_pane1",1,0.5f);
   p=Rwidget_get_child(b,1); demo_print_point(win,p,"rtl_pane2",1,0.5f);
   p=Rwidget_get_child(b,0); demo_print_point(win,p,"rtl_pane1",0,0.5f); (void)x;(void)y;(void)w;(void)h; } }
 Rshutdown(); return 0; }
