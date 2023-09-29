#include "room.h"

bool Room::is_normal(){
  return input.is_normal();
}

void Room::on_fan(){
  digitalWrite(output, HIGH);
  fan_state = Device_state::WORK;
}

void Room::off_fan(){
  digitalWrite(output, LOW);
  fan_state = Device_state::REST;
}

void Room::on_fan_out(){
  digitalWrite(output, HIGH);
  fan_state = Device_state::WORK_OUT;
}

void Bathroom::direct_fan(){
  if (!is_normal() && fan_state == Device_state::REST){
    on_fan();
    p_other_room->on_fan_out();
  }

  if (is_normal() && fan_state == Device_state::WORK){
    off_fan();
  }
}

void Toilet::direct_fan(){
  if (!is_normal() && fan_state == Device_state::REST){
    on_fan();
  }
  
  if (is_normal() && fan_state != Device_state::REST && p_other_room->is_normal()){
    off_fan();
  }
}
