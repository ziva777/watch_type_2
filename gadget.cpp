#include "gadget.h"

#include <Arduino.h>

Display::Display() {

}

void Display::setup() {
    pinMode(Pin::CONTRAST, OUTPUT);
    pinMode(Pin::BRIGHTNESS, OUTPUT);

    analogWrite(Pin::CONTRAST, 55);
    analogWrite(Pin::BRIGHTNESS, 1);

    _lcd.begin(16, 2);
}

void Display::clock_print(uint8_t h, uint8_t m, uint8_t s) {
    _display_buff_memset();
    sprintf(_display_buff, "%2u:%02u:%02u", h, m, s);
    _lcd.setCursor(0, 0);
    _lcd.print(_display_buff);
}

void Display::alarm_print(uint8_t h, uint8_t m) {
    _display_buff_memset();
    sprintf(_display_buff, "%2u:%02u", h, m);
    _lcd.setCursor(0, 1);
    _lcd.print(_display_buff);
}

void Display::_display_buff_memset(char c) {
    memset(_display_buff, c, _display_buff_len);
}

// void Oscillator::sync() {

// }
