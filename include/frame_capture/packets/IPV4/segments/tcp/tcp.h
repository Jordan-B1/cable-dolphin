#ifndef __TCP_H__
#define __TCP_H__

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>

bool display_tcp_packet_info(const u_int8_t *packet, const size_t packet_len);

#endif // __TCP_H__
