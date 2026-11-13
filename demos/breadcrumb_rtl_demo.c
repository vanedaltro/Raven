#include "common.h"
static Rid g_log[4]; static int g_n; static char g_lines[4][128];
static void on_click(Rid b, int i, void* u){ const char* which=(const char*)u; char line[128];
 snprintf(line,sizeof line,"#%d  %s breadcrumb opened: \"%s\" (index %d)",++g_n,which,Rbreadcrumb_get_item_text(b,i),i);
 for(int k=0;k<3;k++) strcpy(g_lines[k],g_lines[k+1]); strcpy(g_lines[3],line);
 for(int k=0;k<4;k++) Rlabel_set_text(g_log[k],g_lines[k]); }
static Rid g_ltr,g_rtl; static void f_ltr(Rid b,void*u){(void)b;(void)u;Rwidget_focus(g_ltr);} static void f_rtl(Rid b,void*u){(void)b;(void)u;Rwidget_focus(g_rtl);}
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("Breadcrumb: LTR vs RTL keyboard",600,340,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 Rid row=Rwidget_add_child(root,Rwidget_create(R_WIDGET_HBOX)); Rpanel_set_spacing(row,8); demo_caption(row,"LTR:");
 Rid b1=Rwidget_add_child(row,Rbutton_create("Focus")); Rbutton_set_clicked_callback(b1,f_ltr,NULL);
 g_ltr=Rwidget_add_child(root,Rwidget_create(R_WIDGET_BREADCRUMB)); Rbreadcrumb_set_items(g_ltr,"Home|Documents|Reports|2026"); Rbreadcrumb_set_clicked_callback(g_ltr,on_click,"LTR");
 row=Rwidget_add_child(root,Rwidget_create(R_WIDGET_HBOX)); Rpanel_set_spacing(row,8); demo_caption(row,"RTL (Rwidget_set_direction RTL):");
 Rid b2=Rwidget_add_child(row,Rbutton_create("Focus")); Rbutton_set_clicked_callback(b2,f_rtl,NULL);
 g_rtl=Rwidget_add_child(root,Rwidget_create(R_WIDGET_BREADCRUMB)); Rwidget_set_direction(g_rtl,R_DIRECTION_RTL); Rbreadcrumb_set_items(g_rtl,"Home|Documents|Reports|2026"); Rbreadcrumb_set_clicked_callback(g_rtl,on_click,"RTL");
 demo_caption(root,"Keys pressed on each: Right + Enter, then Left + Enter");
 for(int k=0;k<4;k++){ g_log[k]=demo_caption(root,""); Rlabel_set_color(g_log[k],1,.8f,.3f,1); }
 int p=0; while(Rwait_frame(-1)){ if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(win,b1,"f_ltr",.5f,.5f); demo_print_point(win,b2,"f_rtl",.5f,.5f);} }
 Rshutdown(); return 0; }
