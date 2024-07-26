#ifndef __ARP_H__
#define __ARP_H__

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>

typedef struct arp_packet_t {
    uint16_t hardware_type;
    uint16_t protocol_type;
    uint8_t hardware_address_len;
    uint8_t protocol_address_len;
    uint16_t operation;
    uint64_t sender_hardware_address : 48;
    uint32_t sender_protocol_address;
    uint64_t target_hardware_address : 48;
    uint32_t target_protocol_address;
} arp_packet_t;

bool handle_arp_packet(const u_int8_t *packet);

#endif // __ARP_H__
