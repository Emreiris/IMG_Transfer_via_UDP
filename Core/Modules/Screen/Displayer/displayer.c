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
#include "dma2d.h"
/*
 * lCD Back Light On
 * NOTE : Back light brightness can be changed via connecting to PWM timer pin
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
	lcd_handle.Init.HorizontalSync     = DISPLAYER_HSYNC - 1;
	lcd_handle.Init.VerticalSync       = DISPLAYER_VSYNC - 1;
	lcd_handle.Init.AccumulatedHBP     = DISPLAYER_HSYNC  + DISPLAYER_HBP - 1;
	lcd_handle.Init.AccumulatedVBP     = DISPLAYER_VSYNC  + DISPLAYER_VBP - 1;
	lcd_handle.Init.AccumulatedActiveH = DISPLAYER_HEIGHT + DISPLAYER_VSYNC+ DISPLAYER_VBP - 1;
	lcd_handle.Init.AccumulatedActiveW = DISPLAYER_WIDTH + DISPLAYER_HSYNC+ DISPLAYER_HBP - 1;
	lcd_handle.Init.TotalHeigh = DISPLAYER_HEIGHT + DISPLAYER_VSYNC + DISPLAYER_VBP + DISPLAYER_VFP - 1;
	lcd_handle.Init.TotalWidth = DISPLAYER_WIDTH + DISPLAYER_HSYNC + DISPLAYER_HBP + DISPLAYER_HFP - 1;
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

	lcd_handle.LayerCfg[0].ImageWidth = DISPLAYER_WIDTH;
	lcd_handle.LayerCfg[0].ImageHeight = DISPLAYER_HEIGHT;
	lcd_handle.LayerCfg[0].Backcolor.Blue = 0;
	lcd_handle.LayerCfg[0].Backcolor.Green = 0;
	lcd_handle.LayerCfg[0].Backcolor.Red = 0;

	HAL_LTDC_SetAddress(&lcd_handle, FB_START_ADDRRESS, 0);
    HAL_LTDC_ConfigLayer(&lcd_handle, &lcd_handle.LayerCfg[0], 1);
}

/*
 * param1  : x position of pixel.
 * param2  : y position of pixel.
 * param3  : pixel color in ARGB8888 format(32 bit)
 * retval  : none.
 * brief   : This function draws a pixel to spesific position.
 * XXX: This function defined non-statically, It may be used with lvgl in the future.
 */

void Display_Draw_Pixel(uint16_t pos_x, uint16_t pos_y, uint32_t color)
{
	*(volatile uint32_t *)(lcd_handle.LayerCfg[0].FBStartAdress+(4*(pos_y*lcd_handle.LayerCfg[0].ImageWidth+pos_x))) = color;
}


/* param   : none.
 * retval  : none.
 * brief   : This function fills the screen with black so that initial RAM buffer does not ruin the screen.
 */

void Display_Fill_Black(void)
{
	 for( uint32_t i = 0; i < DISPLAYER_WIDTH*DISPLAYER_HEIGHT; i++ )
	 {
		 *(volatile uint32_t *)(lcd_handle.LayerCfg[0].FBStartAdress+(i*4)) = 0xFF000000; /* Black in ARGB8888*/
	 }
}


/*
 * param1 : x position of image.
 * param2 : y position of image.
 * param3 : width of image.
 * param4 : heigth of image.
 * param5 : image buffer.
 * brief  : This function draws an image to screen with spesified position.
 */

void Display_Draw_Image(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,volatile uint32_t *image)
{
	if( image == NULL )
	{
		return;
	}

	for( uint16_t i = pos_y; i < pos_y+height; i++ )
	{
		for( uint16_t j = pos_x; j < pos_x+width; j++ )
		{
			Display_Draw_Pixel(j, i, *image++);
		}
	}
}


void Display_Draw_Image_DMA2D(uint16_t pos_x, uint16_t pos_y, uint16_t width, uint16_t height,volatile uint32_t *image)
{
	static DMA2D_HandleTypeDef dma_handle;

	dma_handle.Instance       = DMA2D;

	dma_handle.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
	dma_handle.Init.Mode         = DMA2D_M2M;
	dma_handle.Init.OutputOffset = DISPLAYER_WIDTH-width;

	dma_handle.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	dma_handle.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB8888;
	dma_handle.LayerCfg[0].InputOffset = 0;

	HAL_DMA2D_Init(&dma_handle);
	HAL_DMA2D_ConfigLayer(&dma_handle, 0);
	HAL_DMA2D_Start(&dma_handle,(uint32_t)image, FB_START_ADDRRESS+(pos_x+pos_y*DISPLAYER_WIDTH)*4, width, height);
	HAL_DMA2D_PollForTransfer(&dma_handle, 10);

}


