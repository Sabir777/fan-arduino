#include "room.h"

bool Room::is_normal(){
  return input.is_normal_stat();
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

