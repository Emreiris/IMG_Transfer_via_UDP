/*
 * touch_screen.c
 *
 *  Created on: Feb 6, 2021
 *      Author: emrei
 */



#include "i2c.h"

#include <stdint.h>
#include <stdbool.h>

#include "touch_screen.h"
#include "touch_screen_reglist.h"

#define I2C_Handle (&hi2c3)

_Bool Touch_Screen_Ispressed()
{

	uint8_t touch_num;

	HAL_I2C_Mem_Read(I2C_Handle, DEV_ADDRESS_READ , DEV_TOUCH_NUM, I2C_MEMADD_SIZE_8BIT, &touch_num, 1, 10);

	if(touch_num > 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void Touch_Screen_Read(uint16_t *touch_x, uint16_t *touch_y)
{
	 uint8_t ts_x[2] ;
	 uint8_t ts_y[2] ;

	HAL_I2C_Mem_Read(I2C_Handle, DEV_ADDRESS_READ , DEV_TOUCH_X_H, I2C_MEMADD_SIZE_8BIT, &ts_x[0], 1, 10);
	HAL_I2C_Mem_Read(I2C_Handle, DEV_ADDRESS_READ , DEV_TOUCH_X_L, I2C_MEMADD_SIZE_8BIT, &ts_x[1], 1, 10);

	HAL_I2C_Mem_Read(I2C_Handle, DEV_ADDRESS_READ , DEV_TOUCH_Y_H, I2C_MEMADD_SIZE_8BIT, &ts_y[0], 1, 10);
	HAL_I2C_Mem_Read(I2C_Handle, DEV_ADDRESS_READ , DEV_TOUCH_Y_L, I2C_MEMADD_SIZE_8BIT, &ts_y[1], 1, 10);

	*touch_x = ts_x[1] + ((ts_x[0] & 0x0F) << 8);
	*touch_y = ts_y[1] + ((ts_y[0] & 0x0F) << 8);

}


