/*******************************************************************************
 *
 * main.c
 *
 * FreeETarget control loop
 * 
 *******************************************************************************
 *
 * Initialize the hardware and software
 * 
 * Then setup all of the tasks and exit back to freeRTOS
 *
 ******************************************************************************/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "freETarget.h"
#include "json.h"
#include "timer.h"
#include "serial_io.h"
#include "wifi.h"
#include "diag_tools.h"

void app_main(void)
{

/*
 *  Start FreeETarget
 */
    freeETarget_init();

/*
 * Everything is ready, start the threads.  Low task priority number == low priority
 */
   xTaskCreate(freeETarget_target_loop, "freeETarget_target_loop",   4096, NULL, 25, NULL);
   vTaskDelay(1);

   xTaskCreate(freeETarget_synchronous, "freeETarget_synchronous",   4096, NULL, 20, NULL);
   vTaskDelay(1);

   xTaskCreate(freeETarget_json,        "json_task",                 4096, NULL, 15, NULL);
   vTaskDelay(1);

   xTaskCreate(WiFi_tcp_server_task,    "WiFi_tcp_server",           4096, NULL,  5, NULL);
   vTaskDelay(1);
   xTaskCreate(tcpip_accept_poll,       "tcpip_accept_poll",         4096, NULL,  2, NULL);
   vTaskDelay(1);
   xTaskCreate(tcpip_socket_poll,       "tcpip_socket_poll",         4096, NULL,  5, NULL);
   vTaskDelay(1);

   freeETarget_timer_init();

   DLT(DLT_CRITICAL, printf("Running\r\n");)
}
