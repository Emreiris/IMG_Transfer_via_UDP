/*
 * communication_controller.c
 * Author: Emre IRIS
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

/*
 * param  : none.
 * retval : none.
 * brief  : This function prepares udp server and displayer for image transfer.
 */

void Image_Control_Init(void)
{
	UDP_Server_Init();
	Display_Fill_Black();
}


/*
 * param  : none.
 * retval : none.
 * brief  : This function handles runtime image transmission algorithm.
 */

void Image_Control_Runtime(void)
{
	static uint32_t seq_num = 1;
	static frame_step_t frame_step;

	UDP_Server_Runtime_Task();

	memcpy(&seq_num, udp_buffer, 4);

	if( seq_num > 33*34 ) /* too dangerous, It may cause hardfault interrupt */
	{
		return;
	}

	frame_step = Image_Step(seq_num);


	Display_Draw_Image(BUF_X*frame_step.x_step, BUF_Y*frame_step.y_step, BUF_X, BUF_Y,(uint32_t *)&udp_buffer[1]);

	//Display_Draw_Image_DMA2D(BUF_X*frame_step.x_step, BUF_Y*frame_step.y_step, BUF_X, BUF_Y,(uint32_t *)&udp_buffer[1]);

}


/*
 * param  : sequence number which is desired to be converted.
 * retval : frame_step_t type value.
 * brief  : This function converts sequence number into coordinate pair.
 */

static frame_step_t Image_Step(uint32_t seq_num)
{
	frame_step_t frame_step;

	frame_step.x_step = seq_num%30;
	frame_step.y_step = ((uint16_t)(seq_num-frame_step.x_step)/30);

	return frame_step;
}

