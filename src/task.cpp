#include <Arduino.h>
#include <M5Stack.h>


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
   for( ;; )  
    {  
        xSemaphoreTake( xTaskSemaphore, 1000 );    

        printf("-------vTaskTask-----------\n");
    }
}