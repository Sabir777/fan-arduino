#pragma once
#define PIN_IN_TOILET 10
#define PIN_OUT_TOILET 11
#define PIN_IN_BATHROOM 12
#define PIN_OUT_BATHROOM 13

#include "fan.h"
#include "states.h"
#include "timer.h"

class Direct_fan{
  public:
    Direct_fan();
 
  private:
    
    Bathroom state_bathroom = Bathroom::DRY;
    Toilet state_toilet = Toilet::FRESH;

}

