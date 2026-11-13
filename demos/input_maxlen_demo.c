#include "common.h"
static Rid g_win,g_in,g_mirror,g_cap; static int g_step,g_count;
static void changed(Rid i,const char* t,void* u){ (void)i;(void)u; char b[128]; g_count++; snprintf(b,sizeof b,"changed callback #%d: \"%s\"",g_count,t); Rlabel_set_text(g_mirror,b); }
static void key(RKey k, Ruint m){ Rwindow_inject_key(g_win,k,R_TRUE,m); Rwindow_inject_key(g_win,k,R_FALSE,m); }
static void tick(Rid t,void* u){ (void)t;(void)u; g_step++; char b[160];
 if(g_step==1){ key(R_KEY_LEFT,R_MOD_SHIFT); Rlabel_set_text(g_cap,"Step 1: Shift+Left selects \"f\""); }
 if(g_step==2){ Rwindow_inject_text(g_win,"x"); snprintf(b,sizeof b,"Step 2: type \"x\" -> field is now \"%s\" but no callback fired",Rtext_input_get_text(g_in)); Rlabel_set_text(g_cap,b); } }
int main(void){ if(!demo_init()) return 1;
 g_win=Rwindow_create("TextInput: changed callback",600,230,R_WINDOW_DEFAULT); Rwindow_set_position(g_win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,10); Rwindow_set_content(g_win,root);
 demo_caption(root,"Text \"abcdef\", then Rtext_input_set_max_length(input, 3)");
 g_in=Rwidget_add_child(root,Rwidget_create(R_WIDGET_TEXT_INPUT)); Rtext_input_set_text(g_in,"abcdef"); Rtext_input_set_max_length(g_in,3);
 Rtext_input_set_changed_callback(g_in,changed,NULL);
 g_mirror=demo_caption(root,"changed callback: (not called yet)"); g_cap=demo_caption(root,"");
 Rwidget_focus(g_in); Rtimer_create(2.0,R_TRUE,tick,NULL);
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
