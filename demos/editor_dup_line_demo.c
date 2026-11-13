#include "common.h"
static Rid g_ed;
static void dup(Rid b, void* u){ (void)b;(void)u; Rtext_editor_set_cursor(g_ed,0,0); Rtext_editor_insert_text(g_ed,Rtext_editor_get_line(g_ed,0));
 printf("after: \"%s\"\n",Rtext_editor_get_text(g_ed)); fflush(stdout); }
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("TextEditor: duplicate line",560,280,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 demo_caption(root,"Button: Rtext_editor_insert_text(ed, Rtext_editor_get_line(ed, 0)) at 0:0");
 demo_caption(root,"Expected first line: \"hellohello\"");
 Rid btn=Rwidget_add_child(root,Rbutton_create("Duplicate line 0")); Rslot_set_halign(btn,R_HALIGN_LEFT); Rbutton_set_clicked_callback(btn,dup,NULL);
 g_ed=Rwidget_add_child(root,Rtext_editor_create("hello\nworld\nthird line")); Rslot_set_fill(g_ed,1);
 int p=0; while(Rwait_frame(-1)){ if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); demo_print_point(win,btn,"dup",0.5f,0.5f);} }
 Rshutdown(); return 0; }
