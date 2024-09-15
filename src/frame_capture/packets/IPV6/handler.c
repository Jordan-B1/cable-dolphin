#include "frame_capture/packets/IPV6/ipv6.h"

void ipv6_filler(char *buffer /*Must be at least 40 bytes*/,
                 struct in6_addr *addr) {
    sprintf(buffer,
            "%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%"
            "02x%02x",
            (int)addr->s6_addr[0], (int)addr->s6_addr[1], (int)addr->s6_addr[2],
            (int)addr->s6_addr[3], (int)addr->s6_addr[4], (int)addr->s6_addr[5],
            (int)addr->s6_addr[6], (int)addr->s6_addr[7], (int)addr->s6_addr[8],
            (int)addr->s6_addr[9], (int)addr->s6_addr[10],
            (int)addr->s6_addr[11], (int)addr->s6_addr[12],
            (int)addr->s6_addr[13], (int)addr->s6_addr[14],
            (int)addr->s6_addr[15]);
}

bool handle_ipv6_packet(const uint8_t *packet) {
    ipv6_header_t *ipv6_header = (ipv6_header_t *)packet;
    char addr_str[40] = {0};

    PSAFE((ipv6_header->version == 0b0110), ("Unknown ipv6 version...\n"));
    handle_ip_segment(ipv6_header->next_header, ipv6_header->payload_length,
                      packet + sizeof(ipv6_header_t));
    printf("Source: ");
    ipv6_filler(addr_str, &ipv6_header->source_address);
    printf("%s\n", addr_str);
    memset(addr_str, 0, 40);
    ipv6_filler(addr_str, &ipv6_header->destination_address);

    printf("Destination: ");
    printf("%s\n", addr_str);
    return true;
}