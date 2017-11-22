#include <espressif/esp_common.h>
#include <esp8266.h>

#include "WProgram.h"

typedef void (*voidFuncPtr)();

void pinMode(int pin, int mode)
{
    if (mode == OUTPUT) gpio_enable(pin, GPIO_OUTPUT);
    // else if (mode == INPUT_PULLUP) gpio_enable(pin, GPIO_INPUT_PULLUP);
    else gpio_enable(pin, GPIO_INPUT);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    gpio_write(pin, val);
}

void ICACHE_RAM_ATTR delayMicroseconds(unsigned int us)
{
    sdk_os_delay_us(us);
}

unsigned long ICACHE_RAM_ATTR micros() {
    // printf("utime: %u\n", sdk_system_get_time());
    return sdk_system_get_time();
    // return system_get_time();
}

// unsigned long micros()
// {
//     unsigned long value = xthal_get_ccount() / sdk_system_get_cpu_freq();
//     // printf("utime: %u <> %u\n", value, sdk_system_get_time());
//     return value;
// }

// voidFuncPtr globalhandler;
// void callHandler(uint8_t gpio_num)
// {
//     globalhandler();
// }

#define MAX_HANDLERS 16
static voidFuncPtr handlers[MAX_HANDLERS] = { 0 };
void handleGPIO(unsigned char pin)
{
    if (pin < MAX_HANDLERS) {
        // printf("handle gpio %d\n", pin);
        handlers[pin]();
    }
}

void attachInterrupt(uint8_t pin, voidFuncPtr handler, int mode)
{
    gpio_enable(pin, GPIO_INPUT); // this is the pb!!!
    printf("attach interrupt %d\n", pin);
    // globalhandler = handler;
    // gpio_set_interrupt(pin, GPIO_INTTYPE_EDGE_ANY, callHandler);

    if (pin < MAX_HANDLERS) handlers[pin] = handler;
    gpio_set_interrupt(pin, GPIO_INTTYPE_EDGE_ANY, handleGPIO); 
}

void detachInterrupt(uint8_t pin)
{
    gpio_set_interrupt(pin, GPIO_INTTYPE_NONE, NULL);
}
