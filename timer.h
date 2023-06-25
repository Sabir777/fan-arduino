#pragma once

class Timer{
  public:
    Timer(uint32_t dt);
    void start();
    bool is_time();

  private:
    uint32_t t0;
    uint32_t dt;
}
