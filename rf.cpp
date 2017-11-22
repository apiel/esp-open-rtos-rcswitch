#include "task.hpp"
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "RCSwitch.h"

#include <string.h>

class task_rf_t: public esp_open_rtos::thread::task_t
{
private:
    void task()
    {
        printf("start rf task\n");

        RCSwitch mySwitch = RCSwitch();
        mySwitch.enableReceive(12);  // wemos mini d6

        while(true) {
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

task_rf_t task_rf;

extern "C" void user_init(void)
{
    uart_set_baud(0, 115200);
    task_rf.task_create("task_rf");
}
