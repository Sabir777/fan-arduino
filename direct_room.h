#pragma once

#include "global.h"
#include "room.h"

class Direct_rooms{
  public:
    void run(){
      toilet.direct_fan();
      bathroom.direct_fan();
    }
    
  private:
    Toilet toilet{in_toilet, time_switch, time_start_toilet, time_stop_toilet, time_off, out_toilet, &bathroom};
    Bathroom bathroom{in_bathroom, time_switch, time_start_bathroom, time_stop_bathroom, time_off, out_bathroom, &toilet};
};

