#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <stdint.h>
#include "gadget.h"
#include "timer1.h"

class Program {
    public:
        Program();

        void setup();
        void loop();

        void timer1_attach(Timer1::TimerCallbackFunction func);
        void timer1_start();
        void timer1_interrupt();
        
    private:
        // 100 mS
        Timer1::FCPU_SCALES _timer1_scale = Timer1::SCALE_64; 
        uint16_t _timer1_counts = 25000 - 1;

        void _clock_print();
        void _alarm_print();

        void _check_alarm();
};

#endif // _PROGRAM_H_
