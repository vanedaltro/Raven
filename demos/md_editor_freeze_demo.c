#include "common.h"
#include <stdlib.h>
static char* repeat(const char* unit, int reps){ size_t ul=strlen(unit); char* s=malloc(ul*reps+1); for(int i=0;i<reps;i++) memcpy(s+i*ul,unit,ul); s[ul*reps]=0; return s; }
static Rid g_e2; static char* g_s2;
static void load(Rid b, void* u){ (void)b;(void)u; Rtext_editor_set_text(g_e2,g_s2); printf("loaded\n"); fflush(stdout); }
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("TextEditor (Markdown): one 120 KB line",640,400,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,6); Rwindow_set_content(win,root);
 Rid clk=demo_caption(root,""); Rlabel_set_text_size(clk,20); Rlabel_set_color(clk,.4f,1,.4f,1);
 demo_caption(root,"A) \"*a* \" x 30000 = 120 KB on one line (closed stars), Markdown");
 char* s1=repeat("*a* ",30000); Rid e1=Rwidget_add_child(root,Rtext_editor_create(s1)); Rtext_editor_set_language(e1,"Markdown"); Rslot_set_fill(e1,1);
 Rid row=Rwidget_add_child(root,Rwidget_create(R_WIDGET_HBOX)); Rpanel_set_spacing(row,8);
 demo_caption(row,"B) Markdown editor:");
 Rid bt=Rwidget_add_child(row,Rbutton_create("Set text: \"*a \" x 40000 = 120 KB (unclosed stars)")); Rbutton_set_clicked_callback(bt,load,NULL);
 g_s2=repeat("*a ",40000); g_e2=Rwidget_add_child(root,Rtext_editor_create("*a *a *a")); Rtext_editor_set_language(g_e2,"Markdown"); Rslot_set_fill(g_e2,1);
 int p=0; long frames=0; double t0=Rget_time(); char b[128];
 while(Rwait_frame(0.016)){ frames++; snprintf(b,sizeof b,"frame %ld    clock %.1f s",frames,Rget_time()-t0); Rlabel_set_text(clk,b);
  if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(win,e1,"e1",.5f,.5f); demo_print_point(win,bt,"bt",.5f,.5f); } }
 Rshutdown(); return 0; }
