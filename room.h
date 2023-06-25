#pragma once

#include "global.h"

/*
class Fan{
  public:
    Fan(int);
    void on();
    void off();

  private:
    int pin;
};
*/

class Room{
  public:
    Room() = default;
    virtual ~Room() = default;
    virtual bool is_normal(); //узнаю состояние комнаты: если true - значит состояние нормальное: не воняет(туалет) или не сыро(ванная) 
};


class Bathroom: public Room{
  public:
    Bathroom() = delete;
    bool is_normal() override;

  private:
    Room* p_toil;
    Bathroom_state state = Bathroom_state::DRY;
};

class Toilet: public Room{
  public:
    Toilet() = delete;
    bool is_normal() override;

  private:
    Room* p_bath;
    Toilete_state state = Toilete_state::FRESH;
};
