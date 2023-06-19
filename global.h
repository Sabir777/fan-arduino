#pragma once

#include <stdint.h>

const int in_toilet = 5; //вход: освещение туалета
const int out_toilet = 6; //выход: вентилятор туалета
const int in_bathroom = 11; //вход: освещение ванной
const int out_bathroom = 12; //выход: вентилятор ванной
const int time_switch = 30; //время переключения 30 мс: если 30 мс не было дребезга - переход в противоположное состояние
const uint32_t time_start_toilet = 180000; //туалет: время перехода в ненормальный режим - 3 минуты
const uint32_t time_start_bathroom = 180000; //ванная: время перехода в ненормальный режим - 3 минуты
const uint32_t time_stop_toilet = 900000; //туалет: время перехода в нормальный режим - 15 минут
const uint32_t time_stop_bathroom = 1800000; //ванная: время перехода в нормальный режим - 30 минут 
const uint32_t time_off = 2000; //принудительное отключение - в течении 2 секунд(быстро) из выключенного состояния выключателя включить и выключить выключатель

