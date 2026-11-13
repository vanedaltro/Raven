#include "common.h"
static Rid make_dock(Rid parent, RDirection dir, const char* title){
 Rid col=Rwidget_add_child(parent,Rwidget_create(R_WIDGET_VBOX)); Rslot_set_fill(col,1); Rpanel_set_spacing(col,4);
 demo_caption(col,title);
 Rid dock=Rwidget_add_child(col,Rwidget_create(R_WIDGET_DOCK_AREA)); Rslot_set_fill(dock,1);
 Rwidget_set_direction(dock,dir);
 Rid src=Rwidget_create(R_WIDGET_BORDER); Rborder_set_background(src,.20f,.40f,.80f,1);
 Rid l=Rwidget_add_child(src,Rlabel_create("Source panel (R_DOCK_TAB)")); Rlabel_set_text_size(l,15); Rslot_set_halign(l,R_HALIGN_CENTER); Rslot_set_valign(l,R_VALIGN_CENTER);
 Rid files=Rwidget_create(R_WIDGET_BORDER); Rborder_set_background(files,.90f,.50f,.15f,1);
 l=Rwidget_add_child(files,Rlabel_create("Files\n(LEFT 0.25)")); Rlabel_set_text_size(l,15); Rslot_set_halign(l,R_HALIGN_CENTER); Rslot_set_valign(l,R_VALIGN_CENTER);
 Rdock_area_add_panel(dock,src,"Source",R_DOCK_TAB,R_INVALID_ID,0.0f);
 Rdock_area_add_panel(dock,files,"Files",R_DOCK_LEFT,R_INVALID_ID,0.25f);
 return dock; }
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("DockArea: LTR vs RTL",840,420,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_HBOX); Rpanel_set_spacing(root,16); Rwindow_set_content(win,root);
 make_dock(root,R_DIRECTION_LTR,"LTR: Rdock_area_add_panel(Files, R_DOCK_LEFT, 0.25)");
 make_dock(root,R_DIRECTION_RTL,"RTL: same code + Rwidget_set_direction(dock, RTL)");
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
