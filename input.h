#pragma once

#include "switcher.h"

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
    bool is_normal_state();
    void read();
    void read_rest();
    void read_start();
    void read_on();
    void read_stop();

  
  private:
    int input;
    Input_state state = Input_state::REST;
    Timer timer_start; //таймер запуска ненормального режима
    Timer timer_stop; //таймер сброса ненормального режима
};
