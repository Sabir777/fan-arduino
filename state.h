#pragma once

#include <Arduino.h>
#include "timer.h"
#include "switcher.h"
#include "setting.h"

class State;

//Класс Context: класс-интерфейс для получения результата работы состояний
class Context{
  private:
    State* state_; //указатель на состояние

  public:
    Context(State*);
    ~Context();
    bool is_normal();
    void set_state(State*); //устанавливаю новое состояние
};

//Класс State: предок всех состояний
class State{
  protected:
    Context* context_; //указатель на контекст
    Settings* p_set; //настройки для конкретной комнаты
    int input; //цифровой вход микроконтроллера
    
  public:
    State(Settings* p_set, Context* context);
    State(const State&) = default;
    virtual ~State(){}
    void set_context(Context* context);
    virtual void read() = 0;
    virtual bool is_normal() = 0;
};


//Состояние покоя: базовое состояние
class Rest: public State {
  private:
    Switcher switch_on; //получаю состояние включено: переключатель состояния (антидребезг)
    Switcher switch_off; //получаю состояние отключено: переключатель состояния (антидребезг)
    Timer timer_start; //таймер запуска ненормального режима
    Fast_click fast_click; //переключение выходного состояния при быстром повторении базового состояния: если базовое состояние "включено", то нужно отключить и быстро включить выключатель. Если базовое состояние "отключено" то нужно включить и быстро отключить выключатель.

  public:
    Rest(Settings* p_set, Context* context = nullptr);
    Rest(State*); //State* - повышающее преобразование - сюда будут передаваться указатели на производные классы через this
    void read() override;
    bool is_normal() override;
};


//Состояние включено: ненормальный режим
class On: public State {
  private:
    Switcher switch_on; //получаю состояние включено: переключатель состояния (антидребезг)
    Switcher switch_off; //получаю состояние отключено: переключатель состояния (антидребезг)
    Timer timer_stop; //таймер сброса ненормального режима
    Fast_click fast_click_rest; //переход в состояние Rest: базовое состояние выключателя - "отключено". Нужно включить и быстро отключить выключатель
    Fast_click fast_click_force_off; //переход в состояние Off_forced(принудительное отключение вентиляторов при включенном освещении): базовое состояние выключателя - "включено". Нужно отключить и быстро включить выключатель

  public:
    On(State*); //повышающее преобразование - сюда вместо State* будут передаваться указатели на производные классы через this

    void read() override;
    bool is_normal() override;
};


//Состояние принудительного отключения вентиляции при включенном освещении
class Off_forced: public State {
  private:
    Switcher switch_off; //получаю состояние отключено: переключатель состояния (антидребезг)

  public:
    Off_forced(State*);

    void read() override;
    bool is_normal() override;
};


