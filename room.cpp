#include "room.h"

bool Room::is_normal(){
  return room_state == Room_state::NORMAL;
}

void Room::on_fan(){
  digitalWrite(output, HIGH);
  fan_state = Device_state::WORK;
}

void Toilet::on_fan_out(){
  digitalWrite(output, HIGH);
  fan_state = Device_state::WORK_OUT;
}

void Room::off_fan(){
  digitalWrite(output, LOW);
  fan_state = Device_state::REST;
}


/*
Fan::Fan(int pin):pin{pin}{}

void Fan::on(){
  digitalWrite(pin, HIGH);
}

void Fan::off(){
  digitalWrite(pin, LOW);
}
*/
