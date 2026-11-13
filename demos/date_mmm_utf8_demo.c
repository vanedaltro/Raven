#include "common.h"
static const char* ru_m[12]={"Январь","Февраль","Март","Апрель","Май","Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
static const char* ru_d[7]={"Воскресенье","Понедельник","Вторник","Среда","Четверг","Пятница","Суббота"};
int main(void){ if(!demo_init()) return 1;
 char k[32]; for(int i=0;i<12;i++){ snprintf(k,sizeof k,"Raven.Month%d",i+1); Rlocale_set_text("ru",k,ru_m[i]); }
 for(int i=0;i<7;i++){ snprintf(k,sizeof k,"Raven.Day%d",i); Rlocale_set_text("ru",k,ru_d[i]); }
 Rlocale_set_language("ru");
 Rid win=Rwindow_create("DatePicker: MMM with Russian month names",520,440,R_WINDOW_DEFAULT); Rwindow_set_position(win,80,120);
 Rid root=Rwidget_create(R_WIDGET_VBOX); Rpanel_set_spacing(root,8); Rwindow_set_content(win,root);
 demo_caption(root,"Format \"D MMMM YYYY\" (full name, reference):");
 Rid a=Rwidget_add_child(root,Rwidget_create(R_WIDGET_DATE_PICKER)); Rdate_picker_set_date(a,2026,1,15); Rdate_picker_set_format(a,"D MMMM YYYY"); Rslot_set_halign(a,R_HALIGN_LEFT);
 demo_caption(root,"Format \"D MMM YYYY\" (expected \"15 Янв 2026\"):");
 Rid b=Rwidget_add_child(root,Rwidget_create(R_WIDGET_DATE_PICKER)); Rdate_picker_set_date(b,2026,1,15); Rdate_picker_set_format(b,"D MMM YYYY"); Rslot_set_halign(b,R_HALIGN_LEFT);
 Rid spacer=Rwidget_add_child(root,Rwidget_create(R_WIDGET_VBOX)); Rslot_set_fill(spacer,1);
 double t0=Rget_time(); int opened=0;
 while(Rwait_frame(0.05)){ if(!opened && Rget_time()-t0>5.2){ opened=1; Rdate_picker_set_open(b,1);} }
 Rshutdown(); return 0; }
