#include "common.h"
static Rid g_cap, g_btn; static int g_step;
static const char* steps[]={
 "1. Rtheme_set_style_color(NULL, \"danger\", ACCENT, red)",
 "2. Rtheme_set_style_color(NULL, \"big\", ACCENT, blue)   -> blue (last set wins)",
 "3. Rtheme_set_style_color(NULL, \"danger\", ACCENT, green) -> expected GREEN, stays blue",
 "   (docs/THEMES.md: \"between equals, the last one set wins\")"};
static void tick(Rid t, void* u){ (void)t;(void)u;
 if(g_step==0) Rtheme_set_style_color(NULL,"danger",R_COLOR_ACCENT,.88f,.14f,.14f,1);
 if(g_step==1) Rtheme_set_style_color(NULL,"big",R_COLOR_ACCENT,.15f,.35f,.95f,1);
 if(g_step==2) Rtheme_set_style_color(NULL,"danger",R_COLOR_ACCENT,.10f,.70f,.25f,1);
 if(g_step<4){ Rwidget_add_child(g_cap,Rlabel_create(steps[g_step])); } g_step++; }
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("Style order: last one set wins?",640,300,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,14); Rwindow_set_content(win,root);
 Rid pad=Rwidget_add_child(root,Rwidget_create(R_WIDGET_VBOX)); Rpanel_set_spacing(pad,6);
 Rwidget_add_child(pad,Rlabel_create("Button with Class=\"danger big\":"));
 g_btn=Rwidget_add_child(pad,Rbutton_create("Delete")); Rbutton_set_style(g_btn,R_BUTTON_PRIMARY); Rwidget_set_class(g_btn,"danger big"); Rslot_set_halign(g_btn,R_HALIGN_LEFT);
 g_cap=Rwidget_add_child(root,Rwidget_create(R_WIDGET_VBOX)); Rpanel_set_spacing(g_cap,6);
 Rtimer_create(2.0,R_TRUE,tick,NULL);
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
