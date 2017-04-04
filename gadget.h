#ifndef _GADGET_H_
#define _GADGET_H_

#include <stdint.h>
#include <LiquidCrystal.h>

#include "settings.h"

// // Generate series [a ... b]
// template <typename T>
// class SequenceGenerator {
//     public:
//         SequenceGenerator(T a, T b) : _iter(a), _a(a), _b(b), _interval(b - a) {}
//         T value() { return _iter + _a; }
//         void next() { _iter = ++_iter % _interval; }

//     private:
//         T _iter;
//         T _a;
//         T _b;
//         T _interval;
// };

// // Cycle counter [a ... b]
// template <typename T>
// volatile 
// class Counter {
//     public:
//         Counter(T a, T b);

//         void next();
//         bool ready();
//         bool overflow();
//         void reset();

//     private:
//         T _value;
//         bool _ready {false};
// };

class Display {
    public:
        Display();
        void setup();
        void clock_print(uint8_t h, uint8_t m, uint8_t s);
        void alarm_print(uint8_t h, uint8_t m);

    private:
        static const uint8_t _display_buff_len = 17;
        char _display_buff[_display_buff_len];
        LiquidCrystal _lcd {Pin::RS, Pin::ENABLE, Pin::D0, Pin::D1, Pin::D2, Pin::D3};

        void _display_buff_memset(char c = 0);
};

class SecondsScillator {
    public:
        void sync() { (++_ms == 10 ? _ms = 0, _up = true : _up = false); };
        bool up() const { return _up; };

    private:
        volatile uint8_t _ms {0};
        volatile bool _up {false};
};

class Time {
    public:
        uint8_t hour() const { return _hour; };
        uint8_t minute() const { return _minute; };
        uint8_t second() const { return _second; };
        
        void inc_hour() {
            _hour = ++_hour % 24;
        }
        void inc_minute() {
            _minute = ++_minute % 60;
        }
        void inc_second() {
            _second = 0;
        }

        void add_seconds(int16_t s) {
            s %= 3600;

        }

        void second_tick() {
            if (_second != 59) {
                ++_second;
            } else {
                _second = 0;

                if (_minute != 59) {
                    ++_minute;
                } else {
                    _minute = 0;
                    _hour = ++_hour % 24;
                }
            }
        }

    private:
        volatile uint8_t _hour {0}; 
        volatile uint8_t _minute {0}; 
        volatile uint8_t _second {0};
};

class Clock {
    public:
        Clock(SecondsScillator &o) : _seconds_oscillator(o) {};
        void sync() {
            _raw = false;

            if (_seconds_oscillator.up()) {
                _time.second_tick();
                _raw = true;
            }
        };

        bool raw() const { return _raw; };
        const Time & time() const { return _time; }; 

    private:
        SecondsScillator &_seconds_oscillator;
        Time _time;

        volatile bool _raw = true;
};

class Gadget {
    public:
    private:
};

#endif // _GADGET_H_
