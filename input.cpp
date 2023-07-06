#include "input.h"

bool Input::is_normal_state(){
  read();
  return (state == Input_state::REST) || (state == Input_state::START) || (state == Input_state::OFF_FORCED);
}

void Input::read(){
  read_rest();
  read_start();
  read_on();
  read_stop();
  read_off_forced();
}

void Input::read_rest(){
  if (state != Input_state::REST){
    return;
  }

  if (state != prev_state){
    switcher.start();
    prev_state = state;
  }
  
  if (digitalRead(input)){ //значение для режима PULLUP, для INPUT было !digitalRead
    switcher.start();
  }
  
  if (switcher.is_time()){
    state = Input_state::START;
  }
}

void Input::read_start(){
  if (state != Input_state::START){
    return;
  }

  if (state != prev_state){
    timer_start.start();
    switcher.start();
    prev_state = state;
  }

  if (!digitalRead(input)){ //значение для режима PULLUP, для INPUT было digitalRead
    switcher.start();
  }
  
  if (switcher.is_time()){
    state = Input_state::REST;
  }

  if (timer_start.is_time()){
    state = Input_state::ON;
  }
}

void Input::read_on(){
  if (state != Input_state::ON){
    return;
  }

  if (state != prev_state){
    timer_off.start();
    switcher.start();
    prev_state = state;
  }

  if (!digitalRead(input)){ //значение для режима PULLUP, для INPUT было digitalRead
    switcher.start();
  }

  if (!timer_off.is_time() && switcher.is_time()){ //если быстро отключить выключатель после включения то вентилятор отключится - принудительное отключение
    state = Input_state::REST;
    return;
  } 
  
  if (switcher.is_time()){
    state = Input_state::STOP;
  }
}

void Input::read_stop(){
  if (state != Input_state::STOP){
    return;
  }

  if (state != prev_state){
    timer_stop.start();
    timer_off_for_on.start();
    switcher.start();
    prev_state = state;
  }

  if (digitalRead(input)){ //значение для режима PULLUP, для INPUT было !digitalRead
    switcher.start();
  }

  if (!timer_off_for_on.is_time() && switcher.is_time()){ //если быстро включить выключатель после отключения то вентилятор отключится - принудительное отключение
    state = Input_state::OFF_FORCED; //переход в состояние принудительной остановки
    return;
  } 

  if (switcher.is_time()){
    state = Input_state::ON;
  }

  if (timer_stop.is_time()){
    state = Input_state::REST;
  }
}


void Input::read_off_forced(){
  if (state != Input_state::OFF_FORCED){
    return;
  }

  if (state != prev_state){
    switcher.start();
    prev_state = state;
  }

  if (!digitalRead(input)){ //сброс таймера переключателя при включенном освещении
    switcher.start();
  }

  if (switcher.is_time()){
    state = Input_state::REST;
  }
}

