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

void Display_Draw_Pixel (uint16_t Xpos, uint16_t Ypos, uint32_t color);

void Display_Fill_Black(void);

void Display_Draw_Image(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height, volatile uint32_t *image);

void Display_Draw_Image_DMA2D(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,volatile uint32_t *image);

#endif /* MODULES_SCREEN_DISPLAYER_DISPLAYER_H_ */
