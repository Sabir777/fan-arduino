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

  prev_state = state;

  if (switcher(!digitalRead(input))){ //если выключатель ВКЛЮЧЕН (режим входа: PULLUP), переход в состояние START
    state = Input_state::START;
  }
}

void Input::read_start(){
  if (state != Input_state::START){
    return;
  }

  if (state != prev_state){ //запуск таймера только в начале состояния
    timer_start.start();
    prev_state = state;
  }

  if (switcher(digitalRead(input))){ //если выключатель ОТКЛЮЧЕН (режим входа: PULLUP), переход в состояние REST
    state = Input_state::REST;
  }

  if (timer_start.is_time()){ //если за отведенное время выключатель не отключился, переход в состояние ON
    state = Input_state::ON;
  }
}

void Input::read_on(){
  if (state != Input_state::ON){
    return;
  }

  if (state != prev_state){
    timer_off.start();
    prev_state = state;
  }

  bool state_off = switcher(digitalRead(input)); //true - выключатель отключен

  if (state_off && !timer_off.is_time()){ //если быстро отключить выключатель после включения то вентилятор отключится - принудительное отключение
    state = Input_state::REST;
    return;
  } 
  
  if (state_off){
    state = Input_state::STOP;
  }
}

void Input::read_stop(){
  if (state != Input_state::STOP){
    return;
  }

  if (state != prev_state){
    timer_stop.start();
    timer_off_forced.start();
    prev_state = state;
  }


  bool state_on = switcher(!digitalRead(input)); //true - выключатель включен

  if (state_on && !timer_off_forced.is_time()){ //если быстро включить выключатель после отключения то вентилятор отключится - принудительное отключение
    state = Input_state::OFF_FORCED; //переход в состояние принудительной остановки
    return;
  } 

  if (state_on){
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

  prev_state = state;

  bool state_off = switcher(digitalRead(input)); //true - выключатель отключен

  if (state_off){
    state = Input_state::REST;
  }
}

