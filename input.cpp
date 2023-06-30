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
  if (state != Input_state::START){
    return;
  }

  timer_start.start();

  if (digitalRead(input)){
    switcher.start();
  }
  
  if (switcher.is_time()){
    state = Input_state::REST;
    timer_start.stop();
  }

  if (timer_start.is_time()){
    state = Input_state::ON;
    timer_start.stop();
  }
}

void Input::read_on(){
  if (state != Input_state::ON){
    return;
  }

  if (digitalRead(input)){
    switcher.start();
  }

  if (switcher.is_time()){
    state = Input_state::STOP;
  }
}

void Input::read_stop(){
  if (state != Input_state::STOP){
    return;
  }

  timer_stop.start();

  if (!digitalRead(input)){
    switcher.start();
  }

  if (switcher.is_time()){
    state = Input_state::ON;
    timer_stop.stop();
  }

  if (timer_stop.is_time()){
    state = Input_state::REST;
    timer_stop.stop();
  }
}

