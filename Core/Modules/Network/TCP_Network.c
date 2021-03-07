/*
 * TCP_Network.c
 *
 *  Created on:  02/2020
 *  Author: Emre iris
 */

#if 0

#include "TCP_Network.h"
#include "lwip/tcp.h"
#include "lwip/netbuf.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "ethernetif.h"
#include "ethernet.h"

#include <stdint.h>
#include <string.h>

/*
 * @definitions
*/

#define CLIENT_NUM   1
#define CLIENT_PORTS {8080}

/*
 * @variables
 */

char tcp_rx_buf[16];
size_t tracker;


/*
 * @parameter : TCP communication protocol controller struct.
 * @retval    : none.
 * @brief     : This function closes TCP connection. All motorized systems is closed in respect.
 */

static void TCP_Close_Connection(struct tcp_pcb *pcb)
{
      tcp_arg(pcb, NULL);
      tcp_sent(pcb, NULL);
      tcp_recv(pcb, NULL);
      tcp_close(pcb);
}

/*
 * @parameter1 : Unused argument.
 * @parameter2 : TCP communication protocol controller struct.
 * @parameter3 : TCP buffer control struct.
 * @parameter4 : Error state checking struct.
 * @retval     : Function error state returnig value.
 * @brief      : This function Recieves data via TCP/IP protocol and copies into global buffer.
 * */

static err_t TCP_Recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
	LWIP_UNUSED_ARG(arg);

	if ((err == ERR_OK) && (p != NULL))
	{

		tcp_recved(pcb, p->tot_len);
		memcpy(tcp_rx_buf, (char*)p->payload, p->tot_len);
		pbuf_free(p);

	}
	else
	{
		pbuf_free(p);
	}

	if ((err == ERR_OK) && (p == NULL))
	{
		TCP_Close_Connection(pcb);
	}

	return ERR_OK;
}

/*
 * @parameter1 : Unused argument.
 * @parameter2 : TCP communication protocol controller struct.
 * @parameter3 : Error state checking struct.
 * @retval     : Function error state returnig value.
 * @brief      : This function accepts requests from TCP clients.
 */

static err_t TCP_Accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
      LWIP_UNUSED_ARG(arg);
      LWIP_UNUSED_ARG(err);

      tcp_setprio(pcb, TCP_PRIO_NORMAL);
      tcp_recv(pcb, TCP_Recv);
      tcp_err(pcb, NULL);
      tcp_poll(pcb, NULL, 4);

      return ERR_OK;
}

/*
 * @parameter  : none.
 * @retval     : none.,
 * @brief      : This function manages run-time data manipulation.
 * @NOTE       : It must be called in super loop.
 */

void TCP_Server_Runtime_Task()
{

	static struct tcp_pcb *tcp_controller;
	static const uint16_t port_number[CLIENT_NUM] = CLIENT_PORTS;

	tcp_controller = tcp_new();

	if( tcp_bind(tcp_controller, IP_ADDR_ANY, port_number[tracker]) == ERR_OK )
	{
		tcp_controller = tcp_listen(tcp_controller);
		tcp_accept(tcp_controller, TCP_Accept);
		tracker++;
	}
	else
	{
		memp_free(MEMP_TCP_PCB, tcp_controller);
		tracker++;
	}

	if( tracker >= CLIENT_NUM )
		tracker = 0;

}

#endif
