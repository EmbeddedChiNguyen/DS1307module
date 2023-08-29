#include "ds1307.h"

#define DS1307_ADDRESS 0x68
 typedef struct {
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;
}DS1307_STRUCT;
DS1307_STRUCT    ds1307;

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal 
 * @return Decoded decimal value.
 */
uint8_t B2D(uint8_t bin) {
	    return ((bin / 16) * 10) + (bin % 16);
	}

    /**
 * @brief Decodes the raw decimal value stored in registers to binary format.
 * @param bin decimal-coded decimal value 
 * @return Decoded binary value.
 */
uint8_t D2B(uint8_t dec) {
	return ((dec / 10) << 4) | (dec % 10);
}

/**
  * @brief  Set time to the DS1307 registers
  * @param  hi2c user's I2C
  * @param  sec from 0-59  
  * @param  min from 0-59
  * @param  hour from 00-23
  * @param  day from 01-07
  * @param  date from 0-31
  * @param  month from 01-12
  * @param  year 00-99
  * @retval none
  */

void setTime (I2C_HandleTypeDef *hi2c, uint8_t sec, uint8_t min, uint8_t hour, uint8_t day, uint8_t date, uint8_t month, uint16_t year ){
    uint8_t setTime[7];
    setTime[0]=D2B(sec);
    setTime[1]=D2B(min);
    setTime[2]=D2B(hour);
    setTime[3]=D2B(day);
    setTime[4]=D2B(date);
    setTime[5]=D2B(month);
    setTime[6]=D2B(year);
    HAL_I2C_Mem_Write(hi2c, DS1307_ADDRESS<<1 , 0x00 , 1, setTime , 7 , 1000);
}
/**
  * @brief  Get time from the DS1307 that have been stored before
  * @param  hi2c user's I2C
  * @retval none
  */
void getTime(I2C_HandleTypeDef *hi2c){
    uint8_t getTime[7];
    HAL_I2C_Mem_Read(hi2c, DS1307_ADDRESS<<1 , 0x00 , 1, getTime , 7 , 1000);
    ds1307.sec   = B2D(getTime[0]);
    ds1307.min   = B2D(getTime[1]);
    ds1307.hour  = B2D(getTime[2]);
    ds1307.day   = B2D(getTime[3]);
    ds1307.date  = B2D(getTime[4]);
    ds1307.month = B2D(getTime[5]);
    ds1307.year  = B2D(getTime[6]);
}
