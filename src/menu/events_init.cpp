#include <lvgl.h>
#include "events_init.h"
#include <stdio.h>
#include "gui_guider.h"
#include "aws_iot_mqtt.h"



static void bell_sound_handler(lv_obj_t * obj, lv_event_t event)
{
    printf("bell_sound_handler\n");

	switch (event)
	{
		case LV_EVENT_PRESSED:
		{
    		//guider_load_screen(SCR_LOADER);   
			printf("bell_sound_handler\n");

            if(gPubCount > 3)
            {
              ESP.restart();
            }
                   gPubCount++;
            printf("BtnA.wasPressed Test \n");
            //menu_screen_03();
            //M5.Lcd.fillScreen(BLACK);
            //connectAWS();
            Serial.println("");
            publishMessage(88, 99, 00);
            Serial.println("");
            client.loop();
            //digitalWrite(LED, LOW);
            delay(1000);  // MQTTの送信を待つ
            test++;     
		}
			break;
		default:
			break;
	}
}



void main_scr_home_init(lv_ui *ui)
{
	printf("11111111111111111\n");
	lv_obj_set_event_cb(ui->main_btn1, bell_sound_handler);
	//printf("2222222222222222\n");
	//lv_obj_set_event_cb(ui->setup_select_function7_btn, home_imgbtnSetupevent2_handler);

	//lv_obj_set_event_cb(ui->home_back, home_back_handler);

}