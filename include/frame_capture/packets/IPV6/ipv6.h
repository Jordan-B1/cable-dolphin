#ifndef __IPV6_H__
#define __IPV6_H__

#include "frame_capture/packets/IPV4/ipv4.h"
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

typedef struct ipv6_header_t {
    #if defined(_CPU_BIG_ENDIAN) && !defined(__ICCRX__)
    uint8_t version : 4;       
    uint8_t traffic_class_h : 4;
    uint8_t traffic_class_l : 4; 
    uint8_t flow_label_h : 4;
 #else
    uint8_t traffic_class_h : 4; 
    uint8_t version : 4;
    uint8_t flow_label_h : 4;    
    uint8_t traffic_class_l : 4;
    #endif
    uint16_t flow_label_l;
    uint16_t payload_length;
    uint8_t next_header;
    uint8_t hop_limit;
    struct in6_addr source_address;
    struct in6_addr destination_address;
} ipv6_header_t;

bool handle_ipv6_packet(const uint8_t *packet);

#endif // __IPV6_H__
