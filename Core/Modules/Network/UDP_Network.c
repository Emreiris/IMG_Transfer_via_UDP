/*
 * UDP_Network.c
 *
 *  Created on: Mar 7, 2021
 *      Author: emrei
 */

/* TODO : Library is not completed, there will be so much to add.
 * Command sequence will be added, state machine will be built.
 * BMP file will be handled.*/

#include "UDP_Network.h"
#include <stdint.h>
#include <lwip/udp.h>
#include <string.h>
#include <stdlib.h>
#include <lvgl.h>


uint8_t udp_buffer[BUF_SIZE];

static struct udp_pcb *udp_controller;

static void UDP_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	                    const ip_addr_t *addr, u16_t port);

void UDP_Server_Init()
{

	udp_controller = udp_new();
	udp_bind(udp_controller, IP_ADDR_ANY, 1234);

}

void UDP_Server_Runtime_Task()
{

	udp_recv(udp_controller, UDP_Receive, NULL);

}

static void UDP_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{

	if(p->len < BUF_SIZE)
	{
		memcpy(udp_buffer, p->payload, p->len);
	}

	if( p->len > 0)
	{
		pbuf_free(p);
	}

}

