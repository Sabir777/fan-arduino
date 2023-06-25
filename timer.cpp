#include "timer.h"

Timer::Timer(uint32_t dt):dt{dt}{
  start();
}

void Timer::start(){
  t0 = millis();
}

bool Timer::is_time(){
  return (millis() - t0) >= dt;
}
