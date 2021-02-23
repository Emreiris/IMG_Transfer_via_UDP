/*
 * displayer_gui_driver.c
 *
 *  Created on: 1 Şub 2021
 *      Author: emrei
 */

#include "lvgl.h"

#include "displayer_gui_driver.h"
#include "displayer.h"
#include "sdram.h"


static void display_interface(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p);

void Displayer_GUI_Init(void)
{
	  SDRAM_Init();
	  Displayer_Init();

	  lv_init();

	  static lv_disp_buf_t disp_buf;
	  static lv_color_t buf[LV_HOR_RES_MAX * 50];
	  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 50);

	  lv_disp_drv_t disp_drv;
	  lv_disp_drv_init(&disp_drv);
	  disp_drv.flush_cb = display_interface;
	  disp_drv.buffer = &disp_buf;
	  lv_disp_drv_register(&disp_drv);
}

static void display_interface(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p)
{
    int32_t x, y;
    for(y = area->y1; y <= area->y2; y++) {
        for(x = area->x1; x <= area->x2; x++) {
        	Display_Draw_Pixel(x, y, (uint32_t)color_p->full);
            color_p++;
        }
    }

    lv_disp_flush_ready(disp);
}
