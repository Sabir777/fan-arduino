#pragma once

class Fan{
  public:
    Fan(int);
    void on();
    void off();

  private:
    int pin;
};
