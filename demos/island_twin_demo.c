#include "common.h"
static Rid g_win, g_caption; static int g_step;
static void load(const char* look){ char t[512],n[64]; snprintf(n,sizeof n,"Brand%s",look);
 snprintf(t,sizeof t,"<Theme Name=\"%s\" Look=\"%s\"><Style Class=\"danger\" Accent=\"#E02424\"/></Theme>",n,look);
 Rtheme_load_from_memory(t,0); Rtheme_use(n); }
static void tick(Rid t, void* u){ (void)t;(void)u; g_step++;
 if(g_step%2){ load("RavenLight"); Rlabel_set_text(g_caption,"Theme Look=RavenLight: the island's danger button lost its red <Style>"); }
 else { load("RavenDark"); Rlabel_set_text(g_caption,"Theme Look=RavenDark: both danger buttons are red (correct)"); } }
int main(void){ if(!demo_init()) return 1; load("RavenDark");
 const char* x="<Window Title=\"Island keeps theme styles?\" Width=\"640\" Height=\"300\">"
  "<VBox Spacing=\"14\" Padding=\"16\">"
  "<Label Name=\"cap\" Text=\"Theme Look=RavenDark: both danger buttons are red (correct)\"/>"
  "<Label Text=\"Theme: &lt;Style Class=&quot;danger&quot; Accent=&quot;#E02424&quot;/&gt;\"/>"
  "<HBox Spacing=\"24\">"
   "<VBox Spacing=\"6\"><Label Text=\"In the window content\"/><Button Class=\"danger\" Style=\"Primary\" Text=\"Delete (content)\"/></VBox>"
   "<Island Name=\"isl\" ExpandOnHover=\"false\" ExpandOnClick=\"false\"><Label Text=\"folded\" Slot.Padding=\"14,6\"/><VBox Spacing=\"6\" Slot.Padding=\"18,14\" Width=\"220\"><Label Text=\"Inside an &lt;Island&gt;\"/><Button Class=\"danger\" Style=\"Primary\" Text=\"Delete (island)\"/></VBox></Island>"
  "</HBox></VBox></Window>";
 g_win=Rwindow_create_from_xml(x,strlen(x)); Rwindow_set_position(g_win,80,120);
 g_caption=Rwidget_find(g_win,"cap"); Risland_set_expanded(Rwidget_find(g_win,"isl"),R_TRUE); Rlabel_set_text_size(g_caption,15);
 Rtimer_create(2.5,R_TRUE,tick,NULL);
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
