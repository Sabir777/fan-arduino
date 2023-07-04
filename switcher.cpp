#include "switcher.h"

void Switcher::start(){
  counter = 0;
}

bool Switcher::is_time(){
  if (counter >= dt){
    return true;
  }
  counter++;
  return false;
}


void Timer::start(){
  if (!flag_run){
    flag_run = true;
    counter = 0;
  }
}

void Timer::stop(){
  flag_run = false;
}

bool Timer::is_time(){
  if (counter >= dt){
    return true;
  }
  counter++;
  return false;
}
