#pragma once

/*
 *Обработка дребезга контактов
 *
 *Если в течение 50мс не было дребезга
 *то перевожу переключатель в true
 *
*/

class Switcher{
  public:
    Switcher() = delete;
    Switcher(int dt): dt{dt}{}
    void start();
    bool is_time();

  private:
    int dt;
    int counter;
};


class Timer{
  public:
    Timer() = delete;
    Timer(uint32_t dt): dt{dt}{}
    void start();
    bool is_time();

  private:
    uint32_t dt;
    uint32_t counter;
};