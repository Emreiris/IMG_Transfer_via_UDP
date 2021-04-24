/*
 * UDP_Network.c
 *
 * Author: Emre iris
 */

#include "UDP_Network.h"
#include <stdint.h>
#include <lwip/udp.h>
#include <string.h>
#include <stdlib.h>
#include "displayer.h"

uint32_t udp_buffer[BUF_SIZE];

static struct udp_pcb *udp_controller;

static void UDP_Server_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p,
	                    const ip_addr_t *addr, u16_t port);

/*
 * param  : none.
 * retval : none.
 * brief  : This function initializates udp stack pointer and binds.
 */

void UDP_Server_Init()
{
	udp_controller = udp_new();
    udp_bind(udp_controller, IP_ADDR_ANY, 1234);
}

/*
 * param  : none.
 * retval : none.
 * brief  : This function handles runtime UDP task. It is recommended to be modified according to application.
 */

void UDP_Server_Runtime_Task()
{
	udp_recv(udp_controller, UDP_Server_Receive, NULL);
}

/*
 * param1 : void pointer to argument of the function.
 * param2 : struct udp_pcb pointer to udp stack.
 * param3 : struct pbuf pointer to payload stack.
 * param4 : ip_addr_t pointer to ip address of destination.
 * param5 : port number
 * brief  : This function is Callback to receive functionality. It is to receive data. Costumized by developer.
 */

static void UDP_Server_Receive(void *arg, struct udp_pcb *pcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{

	if(p->len <= BUF_SIZE*4)
	{
		memcpy(udp_buffer, (uint32_t *)p->payload, p->len);
	}

	pbuf_free(p);

}


/*
 * param1 : char pointer for payload.
 * param2 : size_t type payload length in term of byte.
 * retval : none.
 * brief  : This function transmits payload.
 */

void UDP_Transmit(char *payload, size_t payload_length)
{
	struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, payload_length, PBUF_RAM);

	memcpy((char *)p->payload, (char *)payload, payload_length);

	udp_send(udp_controller, p);

	pbuf_free(p);

}
