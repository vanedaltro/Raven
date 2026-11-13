#include "common.h"
static int g_calls; static Rid g_last, g_parent, g_child, g_other, g_lbl;
static const char* nm(Rid i){ return i==g_parent?"Parent":i==g_child?"Child":i==g_other?"Other":"none"; }
static void on_sel(Rid tree, Rid item, void* u){ (void)tree;(void)u; g_calls++; g_last=item; char b[128]; snprintf(b,sizeof b,"selection callback: %s  (count %d)",nm(item),g_calls); Rlabel_set_text(g_lbl,b); }
int main(void){ if(!demo_init()) return 1;
 Rid win=Rwindow_create("TreeView: collapse the selected branch",560,320,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 demo_caption(root,"1) click \"Child\"   2) click Parent's arrow to collapse");
 Rid tree=Rwidget_add_child(root,Rwidget_create(R_WIDGET_TREE_VIEW)); Rslot_set_fill(tree,1);
 g_parent=Rtree_view_add_item(tree,R_INVALID_ID,"Parent"); g_child=Rtree_view_add_item(tree,g_parent,"Child");
 g_other=Rtree_view_add_item(tree,R_INVALID_ID,"Other");
 Rtree_item_set_expanded(g_parent,1);
 Rtree_view_set_selection_changed_callback(tree,on_sel,NULL);
 g_lbl=demo_caption(root,"selection callback: (none yet)"); Rlabel_set_text_size(g_lbl,18); Rlabel_set_color(g_lbl,1,.8f,.3f,1);
 Rid cur=demo_caption(root,""); Rlabel_set_text_size(cur,18);
 int p=0; char b[128];
 while(Rwait_frame(0.05)){ snprintf(b,sizeof b,"highlighted (Rtree_view_get_selected_item): %s",nm(Rtree_view_get_selected_item(tree))); Rlabel_set_text(cur,b);
  if(!p++){ for(int k=0;k<3;k++) Rdraw_frame(); float x,y,w,h; Rwidget_get_rect(tree,&x,&y,&w,&h);
   for(float yy=2;yy<h;yy+=1){ Rid it=Rtree_view_get_item_at(tree,10,yy); if(it==g_child){ demo_print_xy(win,"child",x+60,y+yy+6); break; } }
   for(float yy=2;yy<h;yy+=1){ Rid it=Rtree_view_get_item_at(tree,10,yy); if(it==g_parent){ demo_print_xy(win,"arrow",x+9,y+yy+6); break; } } } }
 Rshutdown(); return 0; }
