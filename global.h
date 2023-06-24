#pragma once

const int in_toilet = 5; //вход: освещение туалета
const int out_toilet = 6; //выход: вентилятор туалета
const int in_bathroom = 11; //вход: освещение ванной
const int out_bathroom = 12; //выход: вентилятор ванной


enum class Bathroom{
  DRY, WET //DRY - сухо, WET - сыро
};

enum class Toilet{
  FRESH, STINK //FRESH - не воняет, STINK - воняет
};