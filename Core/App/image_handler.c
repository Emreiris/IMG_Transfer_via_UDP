/*
 * communication_controller.c
 *
 *  Created on: 12 Mar 2021
 *      Author: emrei
 */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "displayer.h"
#include "UDP_Network.h"
#include "stm32f7xx_hal.h"

#define X_STEP   (16)
#define Y_STEP   (8)

#define BUF_SIZE (X_STEP*Y_STEP+1) /* +1 for sequence number */

static uint16_t x_step = 0;
static uint16_t y_step = 0;
static uint32_t seq_num = 1;

extern uint32_t udp_buffer[BUF_SIZE];

void Image_Control_Init(void)
{

	UDP_Server_Init();
	Display_Fill_Black();

}


void Image_Control_Runtime(void)
{

	UDP_Server_Runtime_Task();

	memcpy(&seq_num, udp_buffer, 4);

	x_step = seq_num%30;
	y_step = ((uint16_t)(seq_num-x_step)/30);

	Display_Draw_Image(X_STEP*x_step, Y_STEP*y_step, X_STEP, Y_STEP,(uint32_t *)&udp_buffer[1]);



}


