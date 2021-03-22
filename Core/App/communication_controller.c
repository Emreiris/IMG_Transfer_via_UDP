/*
 * communication_controller.c
 *
 *  Created on: 12 Mar 2021
 *      Author: emrei
 */

#include <stdint.h>

#include <lvgl.h>

#define IMG_X (176)
#define IMG_Y (176)

#define IMG_ADDRESS ((uint32_t)0xC0020000)

lv_obj_t *canvas;

lv_color_int_t *img_buffer;

void Communication_Control_Init(void)
{
	  img_buffer = (uint32_t *)IMG_ADDRESS;

	  for(uint32_t i = 0; i < IMG_X*IMG_Y; ++i)
	  {
		  img_buffer[i] = 0;
	  }

	  canvas = lv_canvas_create(lv_scr_act(), NULL);
	  lv_canvas_set_buffer(canvas, img_buffer, IMG_X, IMG_Y, LV_IMG_CF_TRUE_COLOR);
	  lv_obj_align(canvas, NULL, LV_ALIGN_CENTER, 0, 0);
}

void Communication_Control_Runtime(void)
{

}

