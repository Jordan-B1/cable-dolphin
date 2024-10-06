#ifndef __IPV6_H__
#define __IPV6_H__

#include "frame_capture/packets/IPV4/ipv4.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

typedef struct ipv6_header_t {
    uint32_t version_class_flow;
    uint16_t payload_length;
    uint8_t next_header;
    uint8_t hop_limit;
    struct in6_addr source_address;
    struct in6_addr destination_address;
} ipv6_header_t;

bool handle_ipv6_packet(const uint8_t *packet);

#endif // __IPV6_H__
