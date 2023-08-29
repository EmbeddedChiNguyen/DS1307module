#ifndef DS1307_H
#define DS1307_H

#include "main.h"


uint8_t B2D (uint8_t bin);
uint8_t D2B (uint8_t dec);
void getTime(I2C_HandleTypeDef *hi2c);
void setTime (I2C_HandleTypeDef *hi2c ,uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint16_t year );

#endif // DS1307_H
