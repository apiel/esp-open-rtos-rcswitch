#include "task.hpp"
#include "queue.hpp"

#include "espressif/esp_common.h"

#include "esp/uart.h"

#include "RCSwitch.h"

class task_1_t: public esp_open_rtos::thread::task_t
{
public:
    esp_open_rtos::thread::queue_t<uint32_t> queue;
    
private:
    void task()
    {
        printf("task_1_t::task(): start\n");

        // uint32_t count = 0;

        // while(true) {
        //     sleep(1000);
        //     queue.post(count);
        //     count++;
        // }

        RCSwitch mySwitch = RCSwitch();        
    }    
};

/******************************************************************************************************************
 * globals
 *
 */
task_1_t task_1;

esp_open_rtos::thread::queue_t<uint32_t> MyQueue;

/**
 * 
 */
extern "C" void user_init(void)
{
    uart_set_baud(0, 115200);
    
    MyQueue.queue_create(10);
    
    task_1.queue = MyQueue;
    
    task_1.task_create("tsk1");
}
