/*
Класс Switcher удаляет дребезг и передает достоверное состояние входа
*/

#pragma once

#include "timer.h"

class Switcher{
  public:
    Switcher() = delete;
    Switcher(uint32_t t_switch)
    : timer_switch{Timer{t_switch}}
    {}

    bool operator()(bool input_state){ //получаю состояние входа
      if (!input_state){
        timer_switch.start();
      }

      return timer_switch.is_time();
    }
                            
 private:
   Timer timer_switch;
};


