#include "common.h"
static Rid g_group, g_win; static void build(int sel);
static void on_changed(Rid r, int checked, void* u){ (void)r; printf("radio %d -> %d, rebuilding\n",(int)(intptr_t)u,checked); fflush(stdout); build(checked?(int)(intptr_t)u:0); }
static void build(int sel){ Rwidget_clear_children(g_group);
 const char* names[]={"Small","Large"};
 for(int i=0;i<2;i++){ Rid r=Rwidget_add_child(g_group,Rcheckbox_create(names[i])); Rcheckbox_set_style(r,R_CHECKBOX_RADIO);
  Rcheckbox_set_checked(r,i==sel); Rcheckbox_set_changed_callback(r,on_changed,(void*)(intptr_t)i);} }
int main(void){ if(!demo_init()) return 1;
 g_win=Rwindow_create("Radio group rebuilt from its callback",480,220,R_WINDOW_DEFAULT); Rwindow_set_position(g_win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,10); Rwindow_set_content(g_win,root);
 demo_caption(root,"The changed callback rebuilds the options (Rwidget_clear_children + recreate).");
 demo_caption(root,"Click \"Small\":");
 g_group=Rwidget_add_child(root,Rwidget_create(R_WIDGET_VBOX)); Rpanel_set_spacing(g_group,6);
 build(1); int p=0;
 while(Rwait_frame(-1)){ if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(g_win,Rwidget_get_child(g_group,0),"small",0.1f,0.5f);} }
 Rshutdown(); return 0; }
