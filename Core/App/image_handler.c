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

typedef struct
{
	uint16_t x_step;
	uint16_t y_step;
} frame_step_t;

extern uint32_t udp_buffer[BUF_SIZE];

static frame_step_t Image_Step(uint32_t seq_num);

void Image_Control_Init(void)
{

	UDP_Server_Init();
	Display_Fill_Black();

}


void Image_Control_Runtime(void)
{

	static uint32_t seq_num = 1;
	static frame_step_t frame_step;

	UDP_Server_Runtime_Task();

	memcpy(&seq_num, udp_buffer, 4);

	frame_step = Image_Step(seq_num);

	Display_Draw_Image(BUF_X*frame_step.x_step, BUF_Y*frame_step.y_step, BUF_X, BUF_Y,(uint32_t *)&udp_buffer[1]);

}

static frame_step_t Image_Step(uint32_t seq_num)
{
	frame_step_t frame_step;

	frame_step.x_step = seq_num%30;
	frame_step.y_step = ((uint16_t)(seq_num-frame_step.x_step)/30);

	return frame_step;
}

