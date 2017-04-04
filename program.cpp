#include "program.h"
#include "settings.h"
#include "button.h"

#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(Pin::RS, Pin::ENABLE, Pin::D0, Pin::D1, Pin::D2, Pin::D3);
Button button1 {Pin::BUTTON1};
Button button2 {Pin::BUTTON2};
Button button3 {Pin::BUTTON3};
Button button4 {Pin::BUTTON4};

char display_buff[17];
volatile uint8_t display_buff_len = sizeof(display_buff);
volatile uint8_t hour = 0, minute = 0, second = 0;
volatile uint8_t ms = 0;
volatile bool raw = true;

uint8_t alaram_hour = 6, alaram_minute = 20;
bool alarm_on = true;
bool alarm_stoped = false;


Program::Program() {

}

void Program::setup() {
    pinMode(Pin::CONTRAST, OUTPUT);
    pinMode(Pin::BRIGHTNESS, OUTPUT);

    analogWrite(Pin::CONTRAST, 55);
    analogWrite(Pin::BRIGHTNESS, 1);
    lcd.begin(16, 2);

    _clock_print();
    _alarm_print();
}

void Program::timer1_attach(Timer1::TimerCallbackFunction func){
    Timer1::instance().attach(func);
}

void Program::timer1_start() {
    Timer1::instance().start(_timer1_scale, _timer1_counts);
}

void Program::timer1_interrupt() {
    if (++ms == 10) {
        ms = 0;

        if (second != 59) {
            ++second;
        } else {
            second = 0;

            if (minute != 59) {
                ++minute;
            } else {
                hour = ++hour % 24;
            }
        }

        raw = true;
    }
}

void Program::_clock_print() {
    memset(display_buff, 0, 17);
    sprintf(display_buff, "%2u:%02u:%02u", hour, minute, second);
    lcd.setCursor(0, 0);
    lcd.print(display_buff);
}

void Program::_alarm_print() {
    memset(display_buff, 0, 17);
    sprintf(display_buff, "%2u:%02u", alaram_hour, alaram_minute);
    lcd.setCursor(0, 1);
    lcd.print(display_buff);
}

void Program::_check_alarm() {
    static uint8_t beep_counter = 0;
    if (hour == alaram_hour and minute == alaram_minute) {
        if (alarm_on and not alarm_stoped) {
            if (beep_counter < 3)
                tone(6, 440, 50);

            ++beep_counter;
        }
    }

    if (hour == alaram_hour and minute == alaram_minute)
        beep_counter = 0;
}

void Program::loop() {
    button1.update();
    button2.update();
    button3.update();
    button4.update();

    if (button4.pressed() or button4.pressed_repeat()) {
        hour = ++hour % 24;
        _clock_print();
    }

    if (button3.pressed() or button3.pressed_repeat()) {
        minute = ++minute % 60;
        _clock_print();
    }

    if (button2.pressed() or button2.pressed_repeat()) {
        alaram_hour = ++alaram_hour % 24;
        _alarm_print();
    }

    if (button1.pressed() or button1.pressed_repeat()) {
        alaram_minute = ++alaram_minute % 60;
        _alarm_print();
    }

    if (raw) { 
        raw = false;
        _clock_print();
    }

    _check_alarm();

    button1.flop();
    button2.flop();
    button3.flop();
    button4.flop();
}
