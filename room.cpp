#include "fan.h"

Fan::Fan(int pin):pin{pin}{}

void Fan::on(){
  digitalWrite(pin, HIGH);
}

void Fan::off(){
  digitalWrite(pin, LOW);
}
