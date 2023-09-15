#pragma once

#include "room.h"

class Direct_rooms{
  public:
    void run(){
      toilet.direct_fan();
      bathroom.direct_fan();
    }
    
  private:
    Toilet_settings set_toilet; //настройки для туалета
    Bathroom_settings set_bathroom; //настройки для ванной
    Toilet toilet{&set_toilet, &bathroom}; //туалет
    Bathroom bathroom{&set_bathroom, &toilet}; //ванная
};

