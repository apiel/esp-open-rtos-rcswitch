#ifndef WProgram_h
#define WProgram_h

#define ESP8266

#define ICACHE_RAM_ATTR
// #define ICACHE_RAM_ATTR     __attribute__((section(".iram.text")))

// #ifdef ICACHE_FLASH
// #define ICACHE_FLASH_ATTR   __attribute__((section(".irom0.text")))
// #define ICACHE_RAM_ATTR     __attribute__((section(".iram.text")))
// #define ICACHE_RODATA_ATTR  __attribute__((section(".irom.text")))
// #else
// #define ICACHE_FLASH_ATTR
// #define ICACHE_RAM_ATTR
// #define ICACHE_RODATA_ATTR
// #endif /* ICACHE_FLASH */

#include <espressif/esp_common.h>
#include <esp8266.h>

#define HIGH 0x1
#define LOW  0x0

#define INPUT             0x00
// #define INPUT_PULLUP      0x02
#define OUTPUT            0x01

#define CHANGE    0x03

#include "ESPwiring.h"

#endif