#define ESP8266

#include <espressif/esp_common.h>
#include <esp8266.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT             0x00
// #define INPUT_PULLUP      0x02
#define OUTPUT            0x01

#define CHANGE    0x03

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

void delayMicroseconds(unsigned int us)
{
    sdk_os_delay_us(us);
}

// voidFuncPtr globalhandler;
// void callHandler(uint8_t gpio_num)
// {
//     globalhandler();
// }

#define MAX_HANDLERS 16
static voidFuncPtr handlers[MAX_HANDLERS] = { 0 };
void handleGPIO(unsigned char pin)
{
    if (pin < MAX_HANDLERS)
        handlers[pin]();
}

void attachInterrupt(uint8_t pin, voidFuncPtr handler, int mode)
{
    // globalhandler = handler;
    // gpio_set_interrupt(pin, GPIO_INTTYPE_EDGE_ANY, callHandler);

    if (pin < MAX_HANDLERS) handlers[pin] = handler;
    gpio_set_interrupt(pin, GPIO_INTTYPE_EDGE_ANY, handleGPIO); 
}

void detachInterrupt(uint8_t pin)
{
    gpio_set_interrupt(pin, GPIO_INTTYPE_NONE, NULL);
}
