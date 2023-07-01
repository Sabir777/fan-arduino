#pragma once

const int in_toilet = 5; //вход: освещение туалета
const int out_toilet = 6; //выход: вентилятор туалета
const int in_bathroom = 11; //вход: освещение ванной
const int out_bathroom = 12; //выход: вентилятор ванной
const uint32_t time_start_toilet = 180000; //туалет: время перехода в ненормальный режим - 3 минуты
const uint32_t time_start_bathroom = 180000; //ванная: время перехода в ненормальный режим - 3 минуты
const uint32_t time_stop_toilet = 900000; //туалет: время перехода в нормальный режим - 15 минут
const uint32_t time_stop_bathroom = 1800000; //ванная: время перехода в нормальный режим - 30 минут 

