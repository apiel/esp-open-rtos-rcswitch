#include "task.hpp"
#include "queue.hpp"

#include "espressif/esp_common.h"

#include "esp/uart.h"

#include "RCSwitch.h"

#include <string.h>

void my_intr_handler(uint8_t gpio_num) {
    printf("rf handler %d\n", gpio_num);
}

class task_1_t: public esp_open_rtos::thread::task_t
{
public:
    esp_open_rtos::thread::queue_t<uint32_t> queue;
    
private:
    void task()
    {
        printf("task_1_t::task(): start\n");

        RCSwitch mySwitch = RCSwitch();
        mySwitch.enableReceive(12);  // d6
        // gpio_enable(12, GPIO_INPUT);
        // gpio_set_interrupt(12, GPIO_INTTYPE_EDGE_ANY, my_intr_handler);

        while(true) {
            // int pir_value = gpio_read(12);
            // printf("rf pin val %d\n", pir_value);

            if (mySwitch.available()) {
                printf("received\n");
                int value = mySwitch.getReceivedValue();
                
                if (value == 0) {
                    printf("Unknown encoding\n");
                } else {
                    printf("Received %lu / %d bit, Protocol %d\n", mySwitch.getReceivedValue(), 
                                mySwitch.getReceivedBitlength(), mySwitch.getReceivedProtocol());
                }

                mySwitch.resetAvailable();
            }  
        }      
    }    
};

/******************************************************************************************************************
 * globals
 *
 */
task_1_t task_1;

esp_open_rtos::thread::queue_t<uint32_t> MyQueue;

extern "C" void wifi_new_connection(char * ssid, char * password)
{
    printf("Connect to new wifi: %s %s", ssid, password);
    
    struct sdk_station_config config;    
    if(ssid != NULL) {
        strcpy((char*)(config.ssid), ssid);
        
        if(password != NULL) {
            strcpy((char*)(config.password), password);
        }
        else {
            config.password[0] = '\0';
        }
    }
    else {
        config.ssid[0]     = '\0';
        config.password[0] = '\0';
    }    

    sdk_wifi_station_set_config(&config);
    // sdk_wifi_station_disconnect();
    sdk_wifi_station_connect();
}

/**
 * 
 */
extern "C" void user_init(void)
{
    uart_set_baud(0, 115200);
    
    wifi_new_connection("theflag240", "theflag240x");

    MyQueue.queue_create(10);
    
    task_1.queue = MyQueue;
    
    task_1.task_create("tsk1");
}
