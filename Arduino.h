#ifndef ARDUINO_H
#define ARDUINO_H

#ifdef ARDUINO
#include_next <Arduino.h>

#else // ! ARDUINO

#include <stdint.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>

#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

typedef bool boolean;

#define String std::string
#define indexOf find
#define charAt at

#define F(x) x

inline uint8_t digitalRead(uint8_t pin UNUSED) { return 0; };
inline void digitalWrite(uint8_t pin UNUSED, uint8_t value UNUSED) {};

inline void pinMode(uint8_t pin, int mode) {
    std::cout << "pinMode(" << (int) pin << ", "
            << (mode == 0 ? "INPUT" : mode == 1 ? "OUTPUT" : "INPUT_PULLUP")
            << ")" << std::endl;
};

inline void delayMicroseconds(unsigned int t) { sleep(t / 1000000); }; // ???

inline void delay(unsigned long t) {
    sleep(t / 1000);
};

inline void noInterrupts() {};
inline void interrupts() {};

inline unsigned long micros() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // Probably overflows, but this should be OK in 99.99% of all cases, which is enough here.
    return 1000000 * tv.tv_sec + tv.tv_usec;
}

inline unsigned long millis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // Probably overflows, but this should be OK in 99.99% of all cases, which is enough here.
    return 1000*tv.tv_sec + tv.tv_usec/1000;
}

#define HIGH 1
#define LOW 0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define F_CPU 16000000

// Stream

class Stream {
private:
    std::ostream& stream;
public:
    Stream(std::ostream& stream_) : stream(stream_) {};
    void print(char c) { stream << c; };
    void print(const char *c) { stream << c; };
    void print(const std::string& string) { stream << string; };
    void print(int x) { stream << x; };
    void print(int x, std::ios_base& manipulator(std::ios_base&)) { stream << manipulator << x; };
    void println() { stream << std::endl; };
    void println(const std::string& string) { stream << string << std::endl; };
    void println(long x) { stream << x << std::endl; }
};

#define DEC std::dec

#endif // ! ARDUINO

#endif // ARDUINO_H
