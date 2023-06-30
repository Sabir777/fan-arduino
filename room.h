#pragma once

#include "global.h"
#include "input.h"

class Room{ 
  public:
    Room(int m_input, uint32_t start, uint32_t stop, int output, Room* p_room)
    : input{Input(m_input, start, stop)},
    output{output},
    p_other_room{p_room}
    {}
    virtual void direct_fan(); //Управляю вентилятором своей комнаты
    bool is_normal(); //узнаю состояние комнаты: если true - значит состояние нормальное: не воняет(туалет) или не сыро(ванная) 
    void on_fan(); //включение вентилятора из "своей" комнаты
    void off_fan(); //выключение вентилятора
    void on_fan_out(); //включение вентилятора в туалете из ванной
  
  private:
    Input input;
    int output;
    Room* p_other_room; // другая комната: для ванной это будет туалет, а для туалета наоборот
    Device_state fan_state = Device_state::REST; //состояние вентилятора
};

class Bathroom{
  public:
    void direct_fan(); //Управляю из ванной своим вентилятором и вентилятором туалета
}

