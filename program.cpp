#include "program.h"
#include "settings.h"
#include "button.h"

#include <Arduino.h>
#include <LiquidCrystal.h>

Button button1 {Pin::BUTTON1};
Button button2 {Pin::BUTTON2};
Button button3 {Pin::BUTTON3};
Button button4 {Pin::BUTTON4};

uint8_t alaram_hour = 6, alaram_minute = 20;
bool alarm_on = true;
bool alarm_stoped = false;
bool sync_stoped = false;


Program::Program() {

}

void Program::setup() {
    _display.setup();
    _display.clock_print(_primary_clock.time().hour(), 
                         _primary_clock.time().minute(), 
                         _primary_clock.time().second());
    _display.alarm_print(alaram_hour, alaram_minute);
}

void Program::timer1_attach(Timer1::TimerCallbackFunction func){
    Timer1::instance().attach(func);
}

void Program::timer1_start() {
    Timer1::instance().start(_timer1_scale, _timer1_counts);
}

void Program::timer1_interrupt() {
    if (!sync_stoped) {
        _seconds_oscillator.sync();
        _primary_clock.sync();
    }
}

void Program::_check_alarm() {
}

void Program::loop() {
    button1.update();
    button2.update();
    button3.update();
    button4.update();

    

    if (button4.pressed() or button4.pressed_repeat()) {
        _primary_clock.time().inc_hour();
        _display.clock_print(_primary_clock.time().hour(), 
                             _primary_clock.time().minute(), 
                             _primary_clock.time().second());
    }

    if (button3.pressed() or button3.pressed_repeat()) {
        _primary_clock.time().inc_minute();
        _display.clock_print(_primary_clock.time().hour(), 
                             _primary_clock.time().minute(), 
                             _primary_clock.time().second());
    }

    if (button2.pressed() or button2.pressed_repeat()) {
        sync_stoped = button2.is_down();
        _primary_clock.time().inc_second();
        _display.clock_print(_primary_clock.time().hour(), 
                             _primary_clock.time().minute(), 
                             _primary_clock.time().second());
    }

    if (button1.pressed() or button1.pressed_repeat()) {
        alaram_minute = ++alaram_minute % 60;
        _display.clock_print(_primary_clock.time().hour(), 
                             _primary_clock.time().minute(), 
                             _primary_clock.time().second());
    }

    if (_primary_clock.raw()) { 
        _display.clock_print(_primary_clock.time().hour(), 
                             _primary_clock.time().minute(), 
                             _primary_clock.time().second());
    }

    _check_alarm();

    button1.flop();
    button2.flop();
    button3.flop();
    button4.flop();
}
