enum class Device_state{
  REST, WORK
};

enum class Bathroom{
  DRY, WET
};

enum class Toilet{
  FRESH, STINK
};

class Fan{
  public:
    Fan(int);
    void on();
    void off();

  private:
    int pin;
    Device_state st = Device_state::REST;
};
