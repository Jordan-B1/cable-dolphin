#ifndef __UDP_H__
#define __UDP_H__

#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

bool display_udp_packet_info(const uint8_t *packet, const size_t packet_len);

#endif // __UDP_H__
