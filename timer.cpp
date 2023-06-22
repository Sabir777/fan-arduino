#include timer.h

Timer::Timer(int dt):dt{dt}{
  this->start();
}

void Timer::start(){
  this->t0 = millis();
}

bool Timer::is_time(){
  return (millis() - t0) >= dt;
}
