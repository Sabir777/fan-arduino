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
  if (state != Input_state::REST){
    return;
  }

  if (!digitalRead(input)){
    switcher.start();

  if (switcher.is_time()){
    state = Input_state::START;
  }
}

void Input::read_start(){
  static bool flag_on = false;
  static bool flag_rest = false;

  if (state != Input_state::START){
    return;
  }

  if (!flag_on){
    flag_on = true;
    timer_start.start();
  }

  if (digitalRead(input)){
    switcher.start();
  }
  else if (!flag_rest){
    flag_rest = true;
    switcher.start();
  }
  
  if (flag_rest && switcher.is_time()){
    state = Input_state::REST;
    flag_on = false;
    flag_rest = false;
  }

  if (!flag_rest && timer_start.is_time()){
    state = Input_state::ON;
    flag_on = false;
    flag_rest = false;
  }
}

void Input::read_on(){
  static bool flag_stop = false;

  if (state != Input_state::ON){
    return;
  }

  if (digitalRead(input)){
    switcher.start();
  }
  else if (!flag_stop){
    flag_stop = false;
    switcher.start();
  }

  if (flag_stop && switcher.is_time()){
    state = Input_state::STOP;
    flag_stop = false;
  }
}

void Input::read_stop(){
  static bool flag_stop = false;
  static bool flag_on = false;

  if (state != Input_state::STOP){
    return;
  }

  if (!flag_stop){
    timer_stop.start();
    flag_stop = true;
  }

  if (!digitalRead(input)){
    switcher.start();
  }
  else if (!flag_on){
    flag_on = true;
    switcher.start();
  }

  if (flag_on && switcher.is_time()){
    state = Input_state::ON;
    flag_stop = false;
    flag_on = false;
  }

  if (!flag_on && timer_stop.is_time()){
    state = Input_state::REST;
    flag_stop = false;
    flag_on = false;
  }
}

