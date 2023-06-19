#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "input.h"

enum class Device_state{
  REST, WORK, WORK_OUT //REST - состояние покоя, WORK - вентилятор включен, WORK_OUT - вентилятор включен из другой комнаты (например включение вентилятора в туалете от вентилятора в ванной
};

class Room{ 
  public:
    Room(int pin_input, int t_switch, uint32_t t_start, uint32_t t_stop, uint32_t t_off, int pin_output, Room* p_room)
    : input{Input{pin_input, t_switch, t_start, t_stop, t_off}},
    output{pin_output},
    p_other_room{p_room}
    {}
    virtual void direct_fan() = 0; //Управление вентиляторами
    bool is_normal(); //узнаю состояние комнаты: если true - значит состояние нормальное: не воняет(туалет) или не сыро(ванная) 
    void on_fan(); //включение вентилятора из "своей" комнаты
    void off_fan(); //выключение вентилятора
    void on_fan_out(); //внешнее включение - вентилятор в туалете включается из ванной
  
  protected:
    Input input;
    int output;
    Room* p_other_room; // другая комната: для ванной это будет туалет, а для туалета ванная
    Device_state fan_state = Device_state::REST; //состояние вентилятора
};

class Bathroom: public Room{
  public:
    Bathroom() = delete;
    Bathroom(int pin_input, int t_switch, uint32_t t_start, uint32_t t_stop, uint32_t t_off, int pin_output, Room* p_room)
    : Room{pin_input, t_switch, t_start, t_stop, t_off, pin_output, p_room}
    {}
    void direct_fan() override; //Управляю из ванной своим вентилятором и вентилятором туалета
};

class Toilet: public Room{
  public:
    Toilet() = delete;
    Toilet(int pin_input, int t_switch, uint32_t t_start, uint32_t t_stop, uint32_t t_off, int pin_output, Room* p_room)
    : Room{pin_input, t_switch, t_start, t_stop, t_off, pin_output, p_room}
    {}
    void direct_fan() override; //Управляю вентилятором туалета, отключаю его если в ванной нормальное состояние
};
