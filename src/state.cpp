#include "state.h"

//--------------------------Context-----------------------------//

//конструктор Context: устанавливаю контекст в самое первое состояние
Context::Context(State* state)
 : state_{state}{
  state->set_context(this);
}

//Деструктор Context: уничтожаю состояние при завершении программы - никогда не будет применен
Context::~Context(){
  delete state_;
}

//меняю состояние в контексте
void Context::set_state(State* state){ 
  delete state_;
  state_ = state;
}

//считываю состояние: нормальное(true), ненормальное(false)
bool Context::is_normal(){
  state_->read();
  return state_->is_normal();
}

//---------------------------State------------------------------//

//передаю контекст в состояние: применяется один раз при запуске, дальше контекст передается в новые состояния через конструктор копирования
void State::set_context(Context* context){
  context_ = context;
}

//конструктор с параметрами State: применяется один раз при инициализации объекта Context
State::State(Settings* p_set, Context* context)
 : p_set{p_set}, context_{context}, input{p_set->get_input()} 
{}


//----------------------------Rest------------------------------//

//конструктор с параметрами Rest: применяется один раз при инициализации объекта Context
Rest::Rest(Settings* p_set, Context* context)
 : State{p_set, context},
   switch_on{p_set->get_time_switch()},
   switch_off{p_set->get_time_switch()},
   timer_start{p_set->get_time_start()},
   fast_click{p_set->get_time_off()}
{}

//конструктор копирования Rest
Rest::Rest(State* other)
 : State{*other},
   switch_on{p_set->get_time_switch()}, //гарантированное включение 100 мс
   switch_off{p_set->get_time_switch()}, //гарантированное отключение 100 мс
   timer_start{p_set->get_time_start()}, //переход в ненормальный режим при длительном неотключении освещения
   fast_click{p_set->get_time_off()} //для принудительного включения вентилятора - перевод в ненормальный режим (паттерн: включено - отключено - включено)
{}

//возвращаю характеристику состояния
bool Rest::is_normal() {
  return true;
}

//читаю состояние
void Rest::read(){
  bool state_on = switch_on(!digitalRead(input)); //Так как вход PULLUP, то низкий уровень - включенное положение
  bool state_off = switch_off(digitalRead(input)); //Так как вход PULLUP, то высокий уровень - отключенное положение

  if (!state_on){ //при отключенном положении входа - сброс таймера 
    timer_start.start();
  }

  if (timer_start.is_time() || //переход в ненормальный режим по времени
      fast_click(state_on, state_off)) //принудительное включение вентилятора при повторном быстром включении после отключения
  {
    State* on_state = new On{this};
    context_->set_state(on_state);
  }
}

//-----------------------------On-------------------------------//

//конструктор копирования On
On::On(State* other)
 : State{*other}, 
   switch_on{p_set->get_time_switch()}, //гарантированное включение 100 мс
   switch_off{p_set->get_time_switch()}, //гарантированное отключение 100 мс
   timer_stop{p_set->get_time_stop()}, //переход в нормальный режим при длительном отключении освещения
   fast_click_rest{p_set->get_time_off()}, //паттерн отключено - включено - отключено. Принудительное отключение вентилятора при отключенном освещении 
   fast_click_force_off{p_set->get_time_off()} //паттерн включено - отключено - включено. Принудительное отключение вентилятора при включенном освещении
 {}

//возвращаю характеристику состояния
bool On::is_normal() {
  return false;
}

//читаю состояние
void On::read(){
  bool state_on = switch_on(!digitalRead(input)); //Так как вход PULLUP, то низкий уровень - включенное положение
  bool state_off = switch_off(digitalRead(input)); //Так как вход PULLUP, то высокий уровень - отключенное положение

  if (!state_off){ //при включенном положении входа - сброс таймера
    timer_stop.start();
  }

  if (timer_stop.is_time() || //переход в нормальный режим (состояние покоя) по времени
      fast_click_rest(state_off, state_on)) //принудительное отключение вентилятора при повторном быстром отключении освещения после кратковременного включения
  {
    State* rest_state = new Rest{this};
    context_->set_state(rest_state);
  }

  if (fast_click_force_off(state_on, state_off)) //принудительное отключение вентилятора при повторном быстром включении освещения после кратковременного отключения
  {
    State* off_forced_state = new Off_forced{this};
    context_->set_state(off_forced_state);
  }
}

//-----------------------------Off_forced-------------------------------//

//конструктор копирования Rest
Off_forced::Off_forced(State* other)
 : State{*other},
   switch_off{p_set->get_time_switch()} //гарантированное отключение 100 мс
{}

//возвращаю характеристику состояния
bool Off_forced::is_normal(){
  return true;
}

//читаю состояние
void Off_forced::read(){
  bool state_off = switch_off(digitalRead(input)); //Так как вход PULLUP, то высокий уровень - отключенное положение

  if (state_off) //Перевод в состояние покоя при отключении освещения
  {
    State* rest_state = new Rest{this};
    context_->set_state(rest_state);
  }
}

