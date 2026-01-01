#include <Arduino.h>

SerialClass Serial;

const uint8_t pgm_read_byte_near(const void * addr) {
    return *(reinterpret_cast<const uint8_t*>(addr));
}

unsigned long long ullmicros() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000ULL + ts.tv_nsec / 1000;
}
long micros() {
    return static_cast<long>(ullmicros() % 0xFFFFFFFF);
}
void delayMicroseconds(unsigned int us) {
    struct timespec ts;
    ts.tv_sec = us / 1000000;
    ts.tv_nsec = (us % 1000000) * 1000;
    nanosleep(&ts, nullptr);
}
void delay(unsigned long ms) {
    delayMicroseconds(ms * 1000);
}

void pinMode(int pin, int mode) {}
void digitalWrite(int pin, int value) {}