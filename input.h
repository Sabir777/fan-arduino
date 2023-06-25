#pragma once

#include "timer.h"

enum class Input_state{
  REST, START, ON, STOP
};

class Input{
  public:
    Input() = delete;
    Input(int input, uint32_t start, uint32_t stop)
    : input{input},
    timer_start{Timer(start)},
    timer_stop{Timer(stop)}
    {}
    void read();
    bool is_normal_state();
  
  private:
    int input;
    Input_state state = Input_state::REST;
    Timer timer_start; //таймер запуска ненормального режима
    Timer timer_stop; //таймер сброса ненормального режима
};
