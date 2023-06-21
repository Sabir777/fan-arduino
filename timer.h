#pragma once

class Timer{
  public:
    Timer(int dt);
    void start();
    bool is_time();

  private:
    int t0;
    int dt;
}
