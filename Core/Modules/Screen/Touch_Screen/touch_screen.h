/*
 * touch_screen.h
 *
 *  Created on: Feb 6, 2021
 *      Author: emrei
 */

#ifndef MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_H_
#define MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_H_

#include <stdint.h>

_Bool Touch_Screen_Ispressed();

void Touch_Screen_Read(uint16_t *touch_x, uint16_t *touch_y);

#endif /* MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_H_ */
