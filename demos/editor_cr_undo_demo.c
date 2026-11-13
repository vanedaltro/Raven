#include "common.h"
static Rid g_win,g_ed,g_cap; static int g_step;
static void key(RKey k, Ruint m){ Rwindow_inject_key(g_win,k,R_TRUE,m); Rwindow_inject_key(g_win,k,R_FALSE,m); }
static void show(const char* what){ char b[256]; const char* t=Rtext_editor_get_text(g_ed); char vis[64]; int j=0;
 for(int i=0;t[i]&&j<50;i++){ if(t[i]=='\r'){vis[j++]='\\';vis[j++]='r';} else if(t[i]=='\n'){vis[j++]='\\';vis[j++]='n';} else vis[j++]=t[i]; } vis[j]=0;
 snprintf(b,sizeof b,"%s   text=\"%s\"  length=%d",what,vis,Rtext_editor_get_length(g_ed)); Rlabel_set_text(g_cap,b); printf("%s\n",b); fflush(stdout); }
static void tick(Rid t, void* u){ (void)t;(void)u; g_step++;
 switch(g_step){
 case 1: Rtext_editor_set_cursor(g_ed,0,8); show("Caret at end"); break;
 case 2: key(R_KEY_BACKSPACE,0); show("Backspace (deletes X)"); break;
 case 3: key(R_KEY_BACKSPACE,0); show("Backspace (deletes the lone CR)"); break;
 case 4: key(R_KEY_Z,R_MOD_CTRL); show("Undo #1 (expected \"line 1\\r\", length 7)"); break;
 case 5: show("Undo #2 ..."); break;
 case 6: key(R_KEY_Z,R_MOD_CTRL); show("Undo #2 (expected \"line 1\\rX\", length 8)"); break; } }
int main(void){ if(!demo_init()) return 1;
 g_win=Rwindow_create("TextEditor: lone CR + undo",640,260,R_WINDOW_DEFAULT); Rwindow_set_position(g_win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(g_win,root);
 demo_caption(root,"Rtext_editor_create(\"line 1\\rX\")  (classic-Mac line ending)");
 g_cap=demo_caption(root,"");
 g_ed=Rwidget_add_child(root,Rtext_editor_create("line 1\rX")); Rslot_set_fill(g_ed,1); Rwidget_focus(g_ed);
 show("Start"); Rtimer_create(1.6,R_TRUE,tick,NULL);
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
