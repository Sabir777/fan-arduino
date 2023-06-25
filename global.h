#pragma once

const int in_toilet = 5; //вход: освещение туалета
const int out_toilet = 6; //выход: вентилятор туалета
const int in_bathroom = 11; //вход: освещение ванной
const int out_bathroom = 12; //выход: вентилятор ванной

enum class Room_state{
  NORMAL, EXCESS //NORMAL - нормальное состояние, EXCESS - превышение параметра (влажность или запах)
};

enum class Device_state{
  REST, WORK, WORK_OUT //REST - состояние покоя, WORK - вентилятор включен,WORK_OUT - вентилятор включен из другой комнаты (например включение вентилятора в туалете от вентилятора в ванной
};
