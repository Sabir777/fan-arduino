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
  static Switcher switcher(50); 
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

  if switcher.is_time(){
    state = Input_state::START;
    flag_on = false;
  }
}

