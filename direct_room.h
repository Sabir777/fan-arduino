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
    Toilet toilet{in_toilet, time_start_toilet, time_stop_toilet, out_toilet, &bathroom};
    Bathroom bathroom{in_bathroom, time_start_bathroom, time_stop_bathroom, out_bathroom, &toilet};
};

