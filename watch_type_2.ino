#include "program.h"

Program program = Program();

void setup() {
  program.setup();
  program.timer1_attach(timer);
  program.timer1_start();
}

void timer() {
  program.timer1_interrupt(); 
}

void loop() {
  program.loop();
}
