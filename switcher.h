/*
Класс Switcher удаляет дребезг и передает достоверное состояние входа
*/

#pragma once

#include "timer.h"

class Switcher{
  private:
    Timer timer_switch;
   
  public:
    Switcher(uint32_t t_switch)
    : timer_switch{t_switch}
    {}

    bool operator()(bool input_state){ //получаю состояние входа
      if (!input_state){
        timer_switch.start();
      }

      return timer_switch.is_time();
    }
};


// фиксирую провал состояния: включено - отключено - включено. Если повторное включение произошло вовремя формируется true
class Fast_click{
  private:
    Timer time_out;
    bool flag_init;
    bool flag_start;
    bool prev_state_on;
    bool prev_state_off;

  public:
    Fast_click(uint32_t time_out)
    : time_out{time_out},
      flag_init{true},
      flag_start{false}
    {}

// первым параметром в функтор передается базовое состояние: если я хочу отловить паттерн: включено - отключено - включено то первым нужно передавать состояние on, а вторым параметром состояние off. Если я хочу отловить паттерн: отключено - включено - отключено, то первым нужно передать состояние off, а вторым параметром состояние on
    bool operator()(bool state_on, bool state_off){ //получаю true при отключении и быстрым повторном включении

      if (flag_init){ //первый запуск функтора
        prev_state_on = state_on;
        prev_state_off = state_off;
        flag_init = false;
        return false;
      }

      if (!flag_start && state_off && !prev_state_off){
        flag_start = true;
        time_out.start();  
      }

      if (flag_start && state_on && !prev_state_on && !time_out.is_time()){ //true возвращается только один раз - потом создается новое состояние
        return true;
      }

      if (flag_start && time_out.is_time()){ //сбрасываю ожидание если за указанное время не произошло повторное включение
        flag_start = false;
      }

      prev_state_on = state_on;
      prev_state_off = state_off;
      
      return false;
    }
};

