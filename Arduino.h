// Implement basic Arduino stuff for the library to work
#ifndef ARDUINO_H
#define ARDUINO_H

// Required headers
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <time.h>

// Types
#define byte uint8_t
#define boolean bool

// Progmem stuff
#define PROGMEM 
#define PSTR(str) str
#define F(str) str
#define memcpy_P memcpy
#define strcmp_P strcmp
#define sprintf_P sprintf
#define pgm_read_byte pgm_read_byte_near

const uint8_t pgm_read_byte_near(const void * addr);

// Pin stuff
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

// Timing
unsigned long long ullmicros();
long micros();
void delayMicroseconds(unsigned int us);
void delay(unsigned long ms);

#define F_CPU 1000000L

// Fake serial class
class SerialClass {
public:
    void begin(int baud) {}
    void print(const char* msg) {
        printf("%s", msg);
    }
    void println(const char* msg) {
        printf("%s\n", msg);
    }
};

extern SerialClass Serial;



#endif