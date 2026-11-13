#include "common.h"
static Rid g_cb; static Rid g_win,g_first,g_second,g_log[5]; static char g_lines[5][128];
static void logl(const char* s){ for(int k=0;k<4;k++) strcpy(g_lines[k],g_lines[k+1]); snprintf(g_lines[4],128,"%s",s); for(int k=0;k<5;k++) Rlabel_set_text(g_log[k],g_lines[k]); printf("%s\n",s); fflush(stdout); }
static void second_closed(Rid c,int r,void*u){(void)c;(void)u; char b[128]; snprintf(b,sizeof b,"second popup: closed callback (result=%d)",r); logl(b); }
static void first_closed(Rid c,int r,void*u){(void)c;(void)u; char b[128]; snprintf(b,sizeof b,"first popup closed (result=%d) -> Rpopup_open(second)",r); logl(b);
 Rpopup_open(g_win,g_second,40,150,second_closed,NULL); snprintf(b,sizeof b,"  right after Rpopup_open: Rpopup_is_open(second)=%d",Rpopup_is_open(g_second)); logl(b); }
static void open_first(Rid b,void*u){(void)b;(void)u; logl("Rpopup_open(first)"); Rpopup_open(g_win,g_first,40,150,first_closed,NULL); }
static void close_first(Rid b,void*u){(void)b;(void)u; logl("button: Rpopup_close(first, 7)"); Rpopup_close(g_first,7); }
int main(void){ if(!demo_init()) return 1;
 g_win=Rwindow_create("Popup opened from another popup's closed callback",600,360,R_WINDOW_DEFAULT); Rwindow_set_position(g_win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,6); Rwindow_set_content(g_win,root);
 Rid ob=Rwidget_add_child(root,Rbutton_create("Open first popup")); Rslot_set_halign(ob,R_HALIGN_LEFT); Rbutton_set_clicked_callback(ob,open_first,NULL);
 Rid st=demo_caption(root,""); Rlabel_set_text_size(st,17);
 for(int k=0;k<5;k++){ g_log[k]=demo_caption(root,""); Rlabel_set_color(g_log[k],1,.8f,.3f,1); }
 g_first=Rwidget_create(R_WIDGET_BORDER); Rborder_set_background(g_first,.20f,.40f,.80f,1);
 Rid v=Rwidget_add_child(g_first,Rwidget_create(R_WIDGET_VBOX)); Rpanel_set_spacing(v,6); Rslot_set_padding(v,12,12,12,12);
 demo_caption(v,"FIRST popup"); g_cb=Rwidget_add_child(v,Rbutton_create("Close: Rpopup_close(first, 7)")); Rbutton_set_clicked_callback(g_cb,close_first,NULL);
 g_second=Rwidget_create(R_WIDGET_BORDER); Rborder_set_background(g_second,.15f,.60f,.25f,1);
 Rid l=Rwidget_add_child(g_second,Rlabel_create("SECOND popup (should stay open)")); Rlabel_set_text_size(l,18); Rslot_set_padding(l,16,16,16,16);
 int p=0; char b[128];
 while(Rwait_frame(0.05)){ snprintf(b,sizeof b,"Rpopup_is_open: first=%d  second=%d   popup count=%d",Rpopup_is_open(g_first),Rpopup_is_open(g_second),Rwindow_get_popup_count(g_win)); Rlabel_set_text(st,b);
  if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(g_win,ob,"open",.5f,.5f); } 
  { static int pc=0; if(!pc && Rpopup_is_open(g_first)){ static int n=0; if(++n==3){ pc=1; demo_print_point(g_win,g_cb,"close",.5f,.5f);} } } }
 Rshutdown(); return 0; }
