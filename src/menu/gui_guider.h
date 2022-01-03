#ifndef __GUI_GUIDER_H_
#define __GUI_GUIDER_H_

#include <lvgl.h>



typedef struct
{
    lv_obj_t *home;
    lv_obj_t *main_tabview;
    lv_obj_t *main_tab1;
    lv_obj_t *main_tab2;
    lv_obj_t *main_tab3;
    lv_obj_t *main_label;
    lv_obj_t *main_btn1;
    lv_obj_t *main_btn2;
    lv_obj_t *main_btn3;
}lv_ui;


extern void main_scr_home(lv_ui *ui);
extern void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;



#endif