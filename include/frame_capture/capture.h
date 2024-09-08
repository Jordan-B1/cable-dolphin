#ifndef __CAPTURE_H__
#define __CAPTURE_H__

#include "packets/ARP/arp.h"
#include "packets/IPV4/ipv4.h"
#include "packets/IPV6/ipv6.h"
#include "packets/RARP/rarp.h"
#include <net/ethernet.h>
#include <netinet/in.h>
#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct packet_identifier_t {
    uint16_t type;
    char display_name[25];
    bool (*handler)(const u_int8_t *packet);
} packet_identifier_t;

static const packet_identifier_t handled_packets[] = {
    {.type = ETHERTYPE_IP,
     .display_name = "IPV4",
     .handler = handle_ipv4_packet},
    {.type = ETHERTYPE_IPV6,
     .display_name = "IPV6",
     .handler = handle_ipv6_packet},
    {.type = ETHERTYPE_ARP,
     .display_name = "ARP",
     .handler = handle_arp_packet},
    {.type = ETHERTYPE_REVARP,
     .display_name = "Reverse ARP",
     .handler = handle_rarp_packet}};

static const size_t NB_PACKET_HANDLED =
    sizeof(handled_packets) / sizeof(packet_identifier_t);

bool launch_loop_capture(char *device_name);

#endif // __CAPTURE_H__
