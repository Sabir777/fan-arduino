#pragma once

#include <Arduino.h>
#include "timer.h"

enum class Input_state{
  REST, START, ON, STOP, OFF_FORCED
};

class Input{
  public:
    Input() = delete;
    Input(int input, int t_switch, uint32_t t_start, uint32_t t_stop, uint32_t t_off)
    : input{input},
    switcher{Timer{t_switch}},
    timer_start{Timer{t_start}},
    timer_stop{Timer{t_stop}},
    timer_off{Timer{t_off}},
    timer_off_for_on{Timer{t_off}}
    {}
    bool is_normal_state();
    void read();
    void read_rest();
    void read_start();
    void read_on();
    void read_stop();
    void read_off_forced();
  
  private:
    int input;
    Timer switcher; //таймер - переключатель состояние - антидребезг
    Timer timer_start; //таймер запуска ненормального режима
    Timer timer_stop; //таймер сброса ненормального режима
    Timer timer_off; //таймер принудительного отключения при быстром включении-отключении (базовое состояние: свет отключен, режим продувки после отключения света)
    Timer timer_off_for_on; //таймер принудительного отключения при включенном состоянии: чтобы отключить вентилятор когда работает освещение нужно быстро выключить освещение и снова включить его, переход к нормальному алгоритму выключить освещение
    Input_state state = Input_state::REST;
    Input_state prev_state = Input_state::REST;
};
