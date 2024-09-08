#ifndef __UDP_H__
#define __UDP_H__

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>

bool display_udp_packet_info(const u_int8_t *packet, const size_t packet_len);

#endif // __UDP_H__
