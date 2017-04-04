#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <stdint.h>
#include "gadget.h"
#include "timer1.h"

class GadgetFSM {
    public:
        enum COMMON_STATES { 
            S_CLOCK1,
            S_CLOCK2,
            S_ALARM1,
            S_ALARM2,
            S_ALARM3,
            S_SIGNAL,
            S_TIMER1,
            S_TIMER2,
            S_TIMER3,
            S_STOPWATCH
        };

        enum SUBSTATES {
            S_NONE,
            
            // primary_datetime, secondary_datetime
            S_CLOCK_EDIT_SECONDS,
            S_CLOCK_EDIT_MINUTES,
            S_CLOCK_EDIT_HOURS,
            S_CLOCK_EDIT_DAYS,
            S_CLOCK_EDIT_MONTHS,
            S_CLOCK_EDIT_YEARS,

            // alaram1_datetime, alaram2_datetime
            S_ALARM_TYPE1_EDIT_MINUTES,
            S_ALARM_TYPE1_EDIT_HOURS,

            // alaram3_datetime
            S_ALARM_TYPE2_EDIT_MINUTES,
            S_ALARM_TYPE2_EDIT_HOURS,
            S_ALARM_TYPE2_EDIT_DAYS_OF_WEEK,

            // timer1_datetime, timer2_datetime
            S_TIMER_TYPE1_EDIT_SECONDS,
            S_TIMER_TYPE1_EDIT_MINUTES,
            S_TIMER_TYPE1_EDIT_HOURS,

            // timer3_datetime
            S_TIMER_TYPE2_EDIT_DAYS,
            S_TIMER_TYPE2_EDIT_MONTHS,
            S_TIMER_TYPE2_EDIT_YEARS
        };
    private:
};

class Program {
    public:
        Program();

        void setup();
        void loop();

        void timer1_attach(Timer1::TimerCallbackFunction func);
        void timer1_start();
        void timer1_interrupt();
        
    private:
        // Timer1 - 100 mS
        Timer1::FCPU_SCALES _timer1_scale = Timer1::SCALE_64; 
        uint16_t _timer1_counts = 25000 - 1;

        Display _display;

        SecondsScillator _seconds_oscillator;
        Clock _primary_clock {_seconds_oscillator};

        void _check_alarm();
};

#endif // _PROGRAM_H_
