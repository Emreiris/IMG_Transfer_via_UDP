/*
 * UDP_Network.c
 *
 *  Created on: Mar 7, 2021
 *      Author: emrei
 */

#include "UDP_Network.h"
#include <stdint.h>
#include <lwip/udp.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE (256)


char udp_buffer[BUF_SIZE];

uint16_t length;

static struct udp_pcb *udp_controller;
struct pbuf *p;

static void UDP_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	                    const ip_addr_t *addr, u16_t port);

void UDP_Server_Init()
{

	udp_controller = udp_new();

	udp_bind(udp_controller, IP_ADDR_ANY, 1235);

}

void UDP_Server_Runtime_Task()
{

	udp_recv(udp_controller, UDP_Receive, NULL);

}

static void UDP_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{

	length = p->len;

	memcpy(udp_buffer, p->payload, p->len);

}
