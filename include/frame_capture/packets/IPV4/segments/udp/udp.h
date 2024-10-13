#ifndef __UDP_H__
#define __UDP_H__

#include "utils.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

typedef struct udp_header_t {
    uint16_t port_source;
    uint16_t port_destination;
    uint16_t length;
    uint16_t checksum;
} udp_header_t;

bool display_udp_packet_info(const uint8_t *packet, const size_t packet_len);

#endif // __UDP_H__
