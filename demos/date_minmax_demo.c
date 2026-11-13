#include "common.h"
static Rid g_x,g_a,g_lx,g_la; static int g_cx,g_ca;
static void upd(Rid p, Rid l, int n, const char* what){ int y,m,d; Rdate_picker_get_date(p,&y,&m,&d); char b[160]; snprintf(b,sizeof b,"%s: date %04d-%02d-%02d, changed callbacks: %d",what,y,m,d,n); Rlabel_set_text(l,b); }
static void chx(Rid p,int y,int m,int d,void*u){(void)p;(void)y;(void)m;(void)d;(void)u; g_cx++;}
static void cha(Rid p,int y,int m,int d,void*u){(void)p;(void)y;(void)m;(void)d;(void)u; g_ca++;}
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("DatePicker: Min/Max attributes vs set_range",620,330,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 demo_caption(root,"A) attributes Date=\"2026-11-13\" Min=\"2030-01-01\" Max=\"2030-12-31\"");
 g_x=Rwidget_add_child(root,Rwidget_create(R_WIDGET_DATE_PICKER)); Rslot_set_halign(g_x,R_HALIGN_LEFT);
 Rwidget_set_attribute(g_x,"Date","2026-11-13"); Rwidget_set_attribute(g_x,"Min","2030-01-01"); Rwidget_set_attribute(g_x,"Max","2030-12-31");
 Rdate_picker_set_changed_callback(g_x,chx,NULL);
 g_lx=demo_caption(root,""); Rlabel_set_color(g_lx,1,.8f,.3f,1);
 demo_caption(root,"B) Rdate_picker_set_date(2026-11-13) + Rdate_picker_set_range(2030-01-01, 2030-12-31)");
 g_a=Rwidget_add_child(root,Rwidget_create(R_WIDGET_DATE_PICKER)); Rslot_set_halign(g_a,R_HALIGN_LEFT);
 Rdate_picker_set_date(g_a,2026,11,13); Rdate_picker_set_range(g_a,2030,1,1,2030,12,31);
 Rdate_picker_set_changed_callback(g_a,cha,NULL);
 g_la=demo_caption(root,""); Rlabel_set_color(g_la,.5f,.9f,.5f,1);
 int p=0; while(Rwait_frame(0.05)){ upd(g_x,g_lx,g_cx,"A"); upd(g_a,g_la,g_ca,"B");
  if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(win,g_x,"xml",.3f,.5f); demo_print_point(win,g_a,"api",.3f,.5f);} }
 Rshutdown(); return 0; }
