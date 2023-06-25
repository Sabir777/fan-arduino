#include "input.h"

void Input::read(){
  switch(state){
    case Input_state::REST:
      if digitalRead(input){
        timer_start.start();
        state = Input_state::START;
        delay(100) //против дребезга
      }
      break;
  }
}

bool Input::is_normal_state(){
  return (state == Input_state::REST) || (state == Input_state::START);
}

