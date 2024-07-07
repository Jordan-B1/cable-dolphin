#ifndef __IP_H__
#define __IP_H__

#include <netinet/in.h>
#include <sys/types.h>

typedef struct ipv4_header_t {
    u_char version : 4;
    u_char ihl : 4;
    u_char dscp : 6;
    u_char ecn : 2;
    unsigned short length;
    unsigned short id;
    u_char flags : 3;
    unsigned short fragment_offset : 13;
    u_char ttl;
    u_char protocol;
    unsigned short header_checksum;
    u_int32_t source_address;
    u_int32_t destination_address;
    // Maybe more
} ipv4_header_t;

typedef struct ip_protocol_identifier_t {
    u_char p_value;
    char display_name[5];
} ip_protocol_identifier_t;

ip_protocol_identifier_t handled_protocols[] = {
    {.p_value = IPPROTO_TCP, .display_name = "TCP"},
    // {.p_value = IPPROTO_TCP, .display_name = "UDP"}
    };

static const size_t NB_HANDLED_PROTOCOLS = sizeof(handled_protocols) / sizeof(ip_protocol_identifier_t);

#endif // __IP_H__