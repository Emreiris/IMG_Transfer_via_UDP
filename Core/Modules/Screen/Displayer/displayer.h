/*
 * displayer.h
 *
 *  Created on: Jan 30, 2021
 *      Author: emrei
 */

#ifndef MODULES_SCREEN_DISPLAYER_DISPLAYER_H_
#define MODULES_SCREEN_DISPLAYER_DISPLAYER_H_

#include <stdint.h>

void Displayer_Init();

void Display_Draw_Pixel (int16_t Xpos, int16_t Ypos, uint32_t color);

#endif /* MODULES_SCREEN_DISPLAYER_DISPLAYER_H_ */
