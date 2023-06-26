#pragma once

#include "global.h"
#include "input.h"

class Room{ //абстрактный класс: комната
  public:
    Room(int m_input, uint32_t start, uint32_t stop, int output, Room* p_room)
    : input{Input(m_input, start, stop)},
    output{output},
    p_other_room{p_room}
    {}
    virtual void get_state() = 0; //узнаю состояние входа и вычисляю состояние комнаты
    bool is_normal(); //узнаю состояние комнаты: если true - значит состояние нормальное: не воняет(туалет) или не сыро(ванная) 
    void on_fan(); //включение вентилятора из "своей" комнаты
    void off_fan(); //выключение вентилятора
  
  private:
    Input input;
    int output;
    Room* p_other_room; // другая комната: для ванной это будет туалет, а для туалета наоборот
    Room_state room_state = Room_state:NORMAL; // состояние комнаты
    Device_state fan_state = Device_state::REST; //состояние вентилятора
//    Timer timer_start; //таймер запуска ненормального режима
//    Timer timer_stop; //таймер сброса ненормального режима
};


class Bathroom: public Room{
  public:
    Bathroom() = delete;
    Bathroom(int input, int output, Room* p_room)
    : Room{input, output, p_room}
    {}
    bool is_normal() override;
    void get_state() override;

  private:
    Room* p_toil;
    Bathroom_state state = Bathroom_state::DRY;
};

class Toilet: public Room{
  public:
    Toilet() = delete;
    Toilet(int input, int output, Room* p_room)
    : Room{input, output, p_room}
    {}
    void on_fan_out(); //включение вентилятора из ванной

  private:
    Room* p_bath;
    Toilete_state state = Toilete_state::FRESH;
};


