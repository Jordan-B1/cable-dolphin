#ifndef __TCP_H__
#define __TCP_H__

#include <arpa/inet.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define NB_TCP_FLAGS 8

typedef struct tcp_header_t {
    uint8_t source_port;
    uint8_t destination_port;
    uint32_t sequence_number;
    uint32_t ack_number;
    uint8_t offset_reserved;
    uint8_t flags;
    uint16_t window;
    uint16_t checksum;
    uint16_t urgent_pointer;
    // Options & data
} tcp_header_t;


bool display_tcp_packet_info(const uint8_t *packet, const size_t packet_len);

#endif // __TCP_H__
