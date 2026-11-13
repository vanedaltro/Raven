#include "common.h"
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("Table: sort by Name",520,360,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 demo_caption(root,"Click the \"Name\" header to sort the names A to Z");
 Rid t=Rwidget_add_child(root,Rwidget_create(R_WIDGET_TABLE)); Rslot_set_fill(t,1);
 Rtable_add_column(t,"Name",200); Rtable_set_column_fill(t,0,1);
 const char* names[]={"Zoe","Nan","Alice","Inf","Bob"}; for(int i=0;i<5;i++) Rtable_add_row(t,names[i]);
 Rid order=demo_caption(root,""); Rid exp=demo_caption(root,"Expected A-Z: Alice Bob Inf Nan Zoe"); (void)exp;
 int p=0; char buf[256];
 while(Rwait_frame(0.05)){
  buf[0]=0; strcat(buf,"Rows now: "); for(int r=0;r<Rtable_get_row_count(t);r++){ strcat(buf,Rtable_get_cell(t,r,0)); strcat(buf," "); }
  Rlabel_set_text(order,buf);
  if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); float x,y,w,h; Rwidget_get_rect(t,&x,&y,&w,&h); demo_print_xy(win,"header",x+60,y+12); } }
 Rshutdown(); return 0; }
