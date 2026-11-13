#include "common.h"
static Rid g_a,g_b,g_btn,g_cap; static int g_step;
static void tick(Rid t, void* u){ (void)t;(void)u; g_step++;
 if(g_step==1){ Rlabel_set_text(g_cap,"Moving the button into window B (Theme=\"Plain\") with Rwidget_add_child..."); }
 if(g_step==2){ printf("moving button\n"); fflush(stdout); Rwidget_add_child(Rwidget_find(g_b,"box"),g_btn); } }
int main(void){ if(!demo_init()) return 1;
 const char* app="<Theme Name=\"App\" Look=\"RavenDark\"><Style Widget=\"Button\" Accent=\"#E02424\"/></Theme>";
 const char* plain="<Theme Name=\"Plain\" Look=\"RavenLight\"></Theme>";
 Rtheme_load_from_memory(app,0); Rtheme_use("App"); Rtheme_load_from_memory(plain,0);
 const char* xa="<Window Title=\"Window A (app theme App)\" Width=\"360\" Height=\"220\"><VBox Name=\"box\" Spacing=\"10\" Padding=\"14\"><Label Name=\"cap\" Text=\"The button below lives in window A.\"/><Button Name=\"b\" Style=\"Primary\" Text=\"Move me\"/></VBox></Window>";
 const char* xb="<Window Title=\"Window B (Theme=Plain)\" Width=\"360\" Height=\"220\" Theme=\"Plain\"><VBox Name=\"box\" Spacing=\"10\" Padding=\"14\"><Label Text=\"Window B uses the Plain theme.\"/></VBox></Window>";
 g_a=Rwindow_create_from_xml(xa,strlen(xa)); Rwindow_set_position(g_a,80,120);
 g_b=Rwindow_create_from_xml(xb,strlen(xb)); Rwindow_set_position(g_b,460,120);
 g_btn=Rwidget_find(g_a,"b"); g_cap=Rwidget_find(g_a,"cap");
 Rtimer_create(2.5,R_TRUE,tick,NULL);
 while(Rwait_frame(-1)){} Rshutdown(); return 0; }
