#include "switcher.h"

void Switcher::start(){
  counter = 0;
}

bool Switcher::is_time(){
  if (counter >= dt){
    return true;
  }
  ++counter;
  return false;
}


void Timer::start(){
  counter = 0;
}

bool Timer::is_time(){
  if (counter >= dt){
    return true;
  }
  ++counter;
  return false;
}
