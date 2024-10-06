#ifndef __IP_H__
#define __IP_H__

#include "segments/tcp/tcp.h"
#include "segments/udp/udp.h"
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "utils.h"

typedef struct ipv4_header_t {
    uint8_t version_ihl;
    uint8_t tos;
    uint16_t length;
    uint16_t id;
    uint16_t flags_offset;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t header_checksum;
    uint32_t source_address;
    uint32_t destination_address;
    // [TODO] Some options may come here
} ipv4_header_t;

typedef struct ip_protocol_identifier_t {
    uint8_t p_value;
    char display_name[5];
    bool (*displayer)(const uint8_t *packet, size_t packet_len);
} ip_protocol_identifier_t;

static const ip_protocol_identifier_t handled_ip_segment[] = {
    {.p_value = IPPROTO_TCP, .display_name = "TCP", display_tcp_packet_info},
    {.p_value = IPPROTO_UDP, .display_name = "UDP", display_udp_packet_info}};

static const size_t NB_HANDLED_IP_SEGMENTS =
    sizeof(handled_ip_segment) / sizeof(ip_protocol_identifier_t);

bool handle_ipv4_packet(const uint8_t *packet);
bool handle_ip_segment(const uint8_t protocol, size_t packet_len,
                       const uint8_t *packet);
#endif // __IP_H__