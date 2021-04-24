/*
 * touch_screen_reglist.h
 *
 *  Created on: Feb 6, 2021
 *      Author: emrei
 */

#ifndef MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_REGLIST_H_
#define MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_REGLIST_H_

#include <stdint.h>

#define DEV_ADDRESS_READ    ((uint8_t)0x71)
#define DEV_ADDRESS_WRITE   ((uint8_t)0x70)

#define DEV_TOUCH_NUM       ((uint8_t)0x02)
#define DEV_TOUCH_X_H       ((uint8_t)0x03)
#define DEV_TOUCH_X_L       ((uint8_t)0x04)
#define DEV_TOUCH_Y_H       ((uint8_t)0x05)
#define DEV_TOUCH_Y_L       ((uint8_t)0x06)
#endif /* MODULES_SCREEN_TOUCH_SCREEN_TOUCH_SCREEN_REGLIST_H_ */
