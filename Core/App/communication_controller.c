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

#define BUF_SIZE (4*4p)

extern volatile uint32_t udp_buffer[BUF_SIZE];

void Communication_Control_Init(void)
{
	Display_Fill_Black();
}

void Communication_Control_Runtime(void)
{


	Display_Draw_Image(100, 100, 4, 4, udp_buffer);

		//memset(udp_buffer, 0x00, sizeof(uint32_t)*BUF_SIZE);
}

