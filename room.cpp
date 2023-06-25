#include "fan.h"

/*
Fan::Fan(int pin):pin{pin}{}

void Fan::on(){
  digitalWrite(pin, HIGH);
}

void Fan::off(){
  digitalWrite(pin, LOW);
}
*/

bool Bathroom::is_normal(){
  return state == Bathroom_state::DRY;
}

bool Toilet::is_normal(){
  return state == Toilet_state::FRESH;
}
