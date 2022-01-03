#include <lvgl.h>
#include <stdio.h>
#include "gui_guider.h"

lv_ui guider_ui;

void setup_ui(lv_ui *ui)
{
	main_scr_home(ui);
	lv_scr_load(ui->home);
}
