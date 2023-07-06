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

  if (digitalRead(input)){ //значение для режима PULLUP, для INPUT было !digitalRead
    switcher.start();
  }
  
  if (switcher.is_time()){
    state = Input_state::START;
    switcher.start();
  }
}

void Input::read_start(){
  if (state != Input_state::START){
    return;
  }

  timer_start.start();

  if (!digitalRead(input)){ //значение для режима PULLUP, для INPUT было digitalRead
    switcher.start();
  }
  
  if (switcher.is_time()){
    state = Input_state::REST;
    timer_start.stop();
    switcher.start();
  }

  if (timer_start.is_time()){
    state = Input_state::ON;
    timer_start.stop();
    switcher.start();
  }
}

void Input::read_on(){
  if (state != Input_state::ON){
    return;
  }

  timer_off.start();

  if (!digitalRead(input)){ //значение для режима PULLUP, для INPUT было digitalRead
    switcher.start();
  }

  if (!timer_off.is_time() && switcher.is_time()){ //если быстро отключить выключатель после включения то вентилятор отключится - принудительное отключение
    state = Input_state::REST;
    timer_off.stop();
    switcher.start();
  } 

  if (switcher.is_time()){
    state = Input_state::STOP;
    timer_off.stop();
    switcher.start();
  }
}

void Input::read_stop(){
  if (state != Input_state::STOP){
    return;
  }

  timer_stop.start();

  if (digitalRead(input)){ //значение для режима PULLUP, для INPUT было !digitalRead
    switcher.start();
  }

  if (switcher.is_time()){
    state = Input_state::ON;
    timer_stop.stop();
    switcher.start();
  }

  if (timer_stop.is_time()){
    state = Input_state::REST;
    timer_stop.stop();
    switcher.start();
  }
}

