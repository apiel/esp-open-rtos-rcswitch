#ifndef ESPwiring_h
#define ESPwiring_h

typedef void (*voidFuncPtr)();

void pinMode(int pin, int mode);
void digitalWrite(uint8_t pin, uint8_t val);

void ICACHE_RAM_ATTR delayMicroseconds(unsigned int us);

unsigned long ICACHE_RAM_ATTR micros();
void handleGPIO(unsigned char pin);
void attachInterrupt(uint8_t pin, voidFuncPtr handler, int mode);

void detachInterrupt(uint8_t pin);

#endif