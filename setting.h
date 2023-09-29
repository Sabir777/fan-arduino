#pragma once

#include <stdint.h>

/*--------------Настройки для ванной и туалета-------------*/

//Общие настройки для обоих комнат
struct Setting{
  int time_switch = 100; //время переключения состояния - 100 мс: если 100 мс не было дребезга - переход в противоположное состояние
  uint32_t time_start = 120000; //время перехода в ненормальный режим - 2 минуты
  uint32_t time_off = 1000; //принудительное включение, принудительное отключение вентилятора при отключенном освещении, то же самое при включенном освещении
};


//Настройки для туалета
struct Setting_toilet{
  int input = 5; //вход: освещение туалета
  int output = 6; //выход: вентилятор туалета
  uint32_t time_stop = 300000; //туалет: время перехода в нормальный режим - 5 минут
};


//Настройки для ванной
struct Setting_bathroom{
  int input = 11; //вход: освещение ванной
  int output = 12; //выход: вентилятор ванной
  uint32_t time_stop = 1200000; //ванная: время перехода в нормальный режим - 20 минут 
};


//Интерфейс для считывания настроек отдельно для каждой комнаты
class Settings{
  private:
    static const Setting setting;

  protected:
    static const Setting_toilet set_toilet;
    static const Setting_bathroom set_bathroom;

  public:
    int get_time_switch(){
      return setting.time_switch;
    }
  
    uint32_t get_time_start(){ 
      return setting.time_start;
    }

    uint32_t get_time_off(){ 
      return setting.time_off;
    }

    virtual int get_input() = 0;
    virtual int get_output() = 0;
    virtual uint32_t get_time_stop() = 0;
};

class Toilet_settings: public Settings{
  public:
    int get_input() override { return set_toilet.input; }
    int get_output() override { return set_toilet.output; }
    uint32_t get_time_stop() override {return set_toilet.time_stop; }
};

class Bathroom_settings: public Settings{
  public:
    int get_input() override { return set_bathroom.input; }
    int get_output() override { return set_bathroom.output; }
    uint32_t get_time_stop() override {return set_bathroom.time_stop; }
};

