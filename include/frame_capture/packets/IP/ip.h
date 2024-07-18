#ifndef __IP_H__
#define __IP_H__

#include "segments/tcp/tcp.h"
#include "segments/udp/udp.h"
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef struct ipv4_header_t {
    u_int8_t version : 4;
    u_int8_t ihl : 4;
    u_int8_t dscp : 6;
    u_int8_t ecn : 2;
    unsigned short length;
    unsigned short id;
    u_int8_t flags : 3;
    unsigned short fragment_offset : 13;
    u_int8_t ttl;
    u_int8_t protocol;
    unsigned short header_checksum;
    u_int32_t source_address;
    u_int32_t destination_address;
    // Some options may come here
} ipv4_header_t;

typedef struct ip_protocol_identifier_t {
    u_int8_t p_value;
    char display_name[5];
    bool (*displayer)(const u_int8_t *packet, size_t packet_len);
} ip_protocol_identifier_t;

static const ip_protocol_identifier_t handled_ip_segment[] = {
    {.p_value = IPPROTO_TCP, .display_name = "TCP", display_tcp_packet_info},
    {.p_value = IPPROTO_UDP, .display_name = "UDP", display_udp_packet_info}};

static const size_t NB_HANDLED_IP_SEGMENTS =
    sizeof(handled_ip_segment) / sizeof(ip_protocol_identifier_t);

bool handle_ip_packet(const u_int8_t *packet);

#endif // __IP_H__