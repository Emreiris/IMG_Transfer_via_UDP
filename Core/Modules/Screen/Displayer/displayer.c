/*
 * displayer.c
 *
 *  Created on: Jan 30, 2021
 *      Author: emrei
 */

#include <stdint.h>
#include <stdlib.h>

#include "stm32f7xx.h"
#include "displayer.h"
#include "displayer_const.h"

/*
 * lCD Back Light On
 * @NOTE : Back light brightness can be changed via connecting to PWM timer pin
 */

#define LCD_BACKLIGHT_STATE(x) \
	HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, x)

/*
 * LCD Displayer enable disable functionality
 */

#define LCD_DISP_STATE(x) \
	HAL_GPIO_WritePin(GPIOI, GPIO_PIN_12, x)

#define FB_START_ADDRRESS ((uint32_t)0xC0000000)

LTDC_HandleTypeDef lcd_handle;

static void Displayer_Layer_Init(void);

/*
 * param : none.
 * retval: none.
 * brief : This function gets displayer ready to be driven.
 */

void Displayer_Init()
{

	LCD_BACKLIGHT_STATE(1);
	LCD_DISP_STATE(1);

	lcd_handle.Instance = LTDC;
	lcd_handle.Init.HSPolarity = LTDC_HSPOLARITY_AL;
	lcd_handle.Init.VSPolarity = LTDC_VSPOLARITY_AL;
	lcd_handle.Init.DEPolarity = LTDC_DEPOLARITY_AL;
	lcd_handle.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
	lcd_handle.Init.HorizontalSync = (DISPLAYER_HSYNC - 1);
	lcd_handle.Init.VerticalSync = (DISPLAYER_VSYNC - 1);
	lcd_handle.Init.AccumulatedHBP = (DISPLAYER_HSYNC + DISPLAYER_HBP - 1);
	lcd_handle.Init.AccumulatedVBP = (DISPLAYER_VSYNC + DISPLAYER_VBP - 1);
	lcd_handle.Init.AccumulatedActiveH = (DISPLAYER_HEIGHT + DISPLAYER_VSYNC
			+ DISPLAYER_VBP - 1);
	lcd_handle.Init.AccumulatedActiveW = (DISPLAYER_WIDTH + DISPLAYER_HSYNC
			+ DISPLAYER_HBP - 1);
	lcd_handle.Init.TotalHeigh = (DISPLAYER_HEIGHT + DISPLAYER_VSYNC
			+ DISPLAYER_VBP + DISPLAYER_VFP - 1);
	lcd_handle.Init.TotalWidth = (DISPLAYER_WIDTH + DISPLAYER_HSYNC
			+ DISPLAYER_HBP + DISPLAYER_HFP - 1);
	lcd_handle.Init.Backcolor.Blue = 0;
	lcd_handle.Init.Backcolor.Green = 0;
	lcd_handle.Init.Backcolor.Red = 0;

	HAL_LTDC_Init(&lcd_handle);
	Displayer_Layer_Init();

}


/*
 * param : none.
 * retval: none.
 * brief : This function initialises first layer.
 */


static void Displayer_Layer_Init(void)
{

	lcd_handle.LayerCfg[0].WindowX0 = 0;
	lcd_handle.LayerCfg[0].WindowX1 = DISPLAYER_WIDTH;
	lcd_handle.LayerCfg[0].WindowY0 = 0;
	lcd_handle.LayerCfg[0].WindowY1 = DISPLAYER_HEIGHT;
	lcd_handle.LayerCfg[0].PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
	lcd_handle.LayerCfg[0].Alpha = 255;
	lcd_handle.LayerCfg[0].Alpha0 = 0;
	lcd_handle.LayerCfg[0].BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
	lcd_handle.LayerCfg[0].BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
	lcd_handle.LayerCfg[0].FBStartAdress = (uint32_t)0xC0000000;
	lcd_handle.LayerCfg[0].ImageWidth = DISPLAYER_WIDTH;
	lcd_handle.LayerCfg[0].ImageHeight = DISPLAYER_HEIGHT;
	lcd_handle.LayerCfg[0].Backcolor.Blue = 0;
	lcd_handle.LayerCfg[0].Backcolor.Green = 0;
	lcd_handle.LayerCfg[0].Backcolor.Red = 0;
    HAL_LTDC_ConfigLayer(&lcd_handle, &lcd_handle.LayerCfg[0], 1);
	HAL_LTDC_EnableDither(&lcd_handle);
}

/*
 * NOTE : This function will wait for SDRAM to start.
 */

void Display_Draw_Pixel (int16_t Xpos, int16_t Ypos, uint32_t color)
{
	*(__IO uint32_t *)(lcd_handle.LayerCfg[0].FBStartAdress+( 4 * (Ypos * lcd_handle.LayerCfg [0] .ImageWidth + Xpos))) = color;
}


