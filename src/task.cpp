#include <Arduino.h>
//#include <M5Stack.h>
#include <WiFi.h>


static const char *task_str = "Task task is running\r\n"; 
void vTaskTask( void *pvParameters );
SemaphoreHandle_t xTaskSemaphore ;





void task_init(void)
{
    xTaskSemaphore = xSemaphoreCreateBinary();    

    xTaskCreatePinnedToCore(  vTaskTask,
                "Task Task",
                4096,  
                (void*)task_str, 
                1,
                    NULL,
                    1 );    
}


void vTaskTask( void *pvParameters )  
{
    int adjustTimeCount=3600;
    struct tm timeInfo;     //時刻を格納するオブジェクト
    char s[20];             //文字格納用

    int year;
    int mon;
    int mday;
    int hour;
    int min;
    int sec;

    for( ;; )  
    {  
        printf("-------vTaskTask-----------\n");

        xSemaphoreTake( xTaskSemaphore, 1000 );    


        if (WiFi.status() == WL_CONNECTED && adjustTimeCount > 3600)
        {
            configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");//NTPの設定
            getLocalTime(&timeInfo);    //tmオブジェクトのtimeInfoに現在時刻を入れ込む
            sprintf(s, " %04d/%02d/%02d %02d:%02d:%02d",
                    timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
                    timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);    //人間が読める形式に変換
            Serial.print("NTP:");  //時間をシリアルモニタへ出力
            Serial.println(s);  //時間をシリアルモニタへ出力

            year = timeInfo.tm_year + 1900;
            mon = timeInfo.tm_mon + 1;
            mday = timeInfo.tm_mday;
            hour = timeInfo.tm_hour;
            min = timeInfo.tm_min;
            sec = timeInfo.tm_sec;

            adjustTimeCount=0;
        }
        else
        {
            adjustTimeCount++;
        }


        printf(
        "%04d/%02d/%02d %02d:%02d:%02d \n",
        year,
        mon,
        mday,
        hour,
        min,
        sec
        );



        if(hour >= 23)
        {
            hour=0;

        }
        else if(min == 0 && sec == 0)
        {
            hour++;
        }
        

        if(min >= 59)
        {
            min=0;
        }
        else if(sec == 0)
        {
            min++;
        }


        if(sec >= 59)
        {
            sec=0;
        }
        else
        {
            sec++;
        }


        if(hour == 0 &&min == 0 && sec == 0)
        {
            adjustTimeCount = 3600;
        }

    }
}