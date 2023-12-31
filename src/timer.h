#pragma once

#include <stdint.h>
#include <Arduino.h>


class Timer{
  private:
    uint32_t dt; //уставка таймера
    uint32_t t_start; //время запуска таймера

  public:
    Timer(uint32_t dt): dt{dt} {
      start();
    }

    void start(){
      t_start = millis();
    }

    bool is_time(){
      return millis() - t_start >= dt;
    }
};
