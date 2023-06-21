#include timer.h

Timer::Timer(int dt):dt{dt}{ }

void Timer::start(){
  this.t0 = millis();
}
