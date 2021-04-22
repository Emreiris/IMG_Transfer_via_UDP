/*
 * touch_screen_gui_driver.c
 *
 *  Created on: Feb 6, 2021
 *      Author: emrei
 */

/*
 * standart libs
 */

#include <stdbool.h>

/*
 * costum libs
 */

#include "touch_screen_gui_driver.h"
#include "i2c.h"
#include "lvgl.h"
#include "touch_screen.h"

static bool Touch_Screen_Interface(struct _lv_indev_drv_t * indev, lv_indev_data_t * data);

/*
 * @param  = none.
 * @retval = none.
 * @brief  = touch screen gui driver initialization.
 */

void Touch_Screen_Init()
{
	MX_I2C3_Init();

	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = Touch_Screen_Interface;
	lv_indev_drv_register(&indev_drv);
}

/*
 * @param1 = pointer to indev_drv_t type.
 * @param2 = pointer to displayer area type.
 * @retval = always false.
 * @brief  = touch screen gui driver helper function that touches to targeted machine.
 */

static bool Touch_Screen_Interface(struct _lv_indev_drv_t * indev, lv_indev_data_t * data)
{
	uint16_t ts_x;
	uint16_t ts_y;

	data->state = Touch_Screen_Ispressed() ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

	if (data->state == LV_INDEV_STATE_PR)
	{
		Touch_Screen_Read(&ts_x, &ts_y);
	}

	data->point.x = (int16_t)ts_y;
	data->point.y = (int16_t)ts_x;

	return false;
}
