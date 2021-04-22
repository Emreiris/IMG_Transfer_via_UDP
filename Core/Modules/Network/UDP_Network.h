/*
 * UDP_Network.h
 *
 * Author: Emre iris
 */

#ifndef MODULES_NETWORK_UDP_NETWORK_H_
#define MODULES_NETWORK_UDP_NETWORK_H_

#include <stdlib.h>

void UDP_Server_Init();

void UDP_Server_Runtime_Task();

void UDP_Transmit(char *payload, size_t payload_length);

#endif /* MODULES_NETWORK_UDP_NETWORK_H_ */
