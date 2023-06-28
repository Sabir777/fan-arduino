#include "input.h"

bool Input::is_normal_state(){
  read();
  return (state == Input_state::REST) || (state == Input_state::START);
}

void Input::read(){
  read_rest();
  read_start();
  read_on();
  read_stop();
}

void Input::read_rest(){
  static bool flag_on = false;

  if (state != Input_state::REST){
    return;
  }

  if (digitalRead(input) && !flag_on){
    switcher.start();
    flag_on = true;
  }
  else{
    flag_on = false;
  }

  if (switcher.is_time()){
    state = Input_state::START;
    flag_on = false;
  }
}

void Input::read_start(){
  static bool flag_on = false;
  static bool flag_off = false;

  if (state != Input_state::START){
    return;
  }

  if (!flag_on){
    timer_start.start();
  }

  if (!digitalRead(input) && !flag_off){
    switcher.start();
    flag_off = true;
  }
  else{
    flag_off = false;
  }

  if (switcher.is_time()){
    state = Input_state::REST;
    flag_on = false;
    flag_off = false;
  }

  if (!flag_off && timer_start.is_time()){
    state = Input_state::ON;
    flag_on = false;
    flag_off = false;
  }
}

void Input::read_on(){
  static bool flag_off = false;

  if (state != Input_state::ON){
    return;
  }

  if (!digitalRead(input) && !flag_off){
    switcher.start();
    flag_off = true;
  }
  else{
    flag_off = false;
  }

  if (switcher.is_time()){
    state = Input_state::STOP;
    flag_off = false;
  }
}

void Input::read_stop(){
  static bool flag_stop = false;

  if (state != Input_state::STOP){
    return;
  }

  if (!flag_stop){
    timer_stop.start();
    flag_stop = true;
  }

  if (timer_stop.is_time()){
    state = Input_state::REST;
    flag_off = false;
  }
}

