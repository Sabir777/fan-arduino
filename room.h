#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "input.h"

enum class Device_state{
  REST, WORK, WORK_OUT //REST - состояние покоя, WORK - вентилятор включен, WORK_OUT - вентилятор включен из другой комнаты (например включение вентилятора в туалете от вентилятора в ванной
};

class Room{ 
  public:
    Room(int m_input, uint32_t start, uint32_t stop, int output, Room* p_room)
    : input{Input{m_input, start, stop}},
    output{output},
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
    Bathroom(int m_input, uint32_t start, uint32_t stop, int output, Room* p_room)
    : Room{m_input, start, stop, output, p_room}
    {}
    void direct_fan() override; //Управляю из ванной своим вентилятором и вентилятором туалета
};

class Toilet: public Room{
  public:
    Toilet() = delete;
    Toilet(int m_input, uint32_t start, uint32_t stop, int output, Room* p_room)
    : Room{m_input, start, stop, output, p_room}
    {}
    void direct_fan() override; //Управляю вентилятором туалета, отключаю его если в ванной нормальное состояние
};
