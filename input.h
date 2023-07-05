#pragma once

#include <Arduino.h>
#include "switcher.h"

enum class Input_state{
  REST, START, ON, STOP
};

class Input{
  public:
    Input() = delete;
    Input(int input, int t_switch, uint32_t t_start, uint32_t t_stop, uint32_t t_off)
    : input{input},
    switcher{Switcher{t_switch}},
    timer_start{Timer{t_start}},
    timer_stop{Timer{t_stop}},
    timer_off{Timer{t_off}}
    {}
    bool is_normal_state();
    void read();
    void read_rest();
    void read_start();
    void read_on();
    void read_stop();
  
  private:
    int input;
    Switcher switcher; //таймер - переключатель состояние - антидребезг
    Timer timer_start; //таймер запуска ненормального режима
    Timer timer_stop; //таймер сброса ненормального режима
    Timer timer_off; //таймер принудительного отключения при быстром включении-отключении
    Input_state state = Input_state::REST;
};
