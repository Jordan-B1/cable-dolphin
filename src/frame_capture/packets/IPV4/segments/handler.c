#include "frame_capture/packets/IPV4/ipv4.h"

bool handle_ip_segment(const uint8_t protocol, size_t packet_len,
                       const uint8_t *packet) {
    for (int i = 0; i < NB_HANDLED_IP_SEGMENTS; i++) {
        if (protocol == handled_ip_segment[i].p_value) {
            printf("Protocol: %s\n", handled_ip_segment[i].display_name);
            handled_ip_segment[i].displayer(packet, packet_len);
            return true;
        }
        if (i == NB_HANDLED_IP_SEGMENTS - 1 &&
            protocol != handled_ip_segment[i].p_value) {
            printf("Protocol not handled yet...\n");
            return false;
        }
    }
    return false;
}

bool handle_ipv4_packet(const uint8_t *packet) {
    const ipv4_header_t *ip_header = (ipv4_header_t *)packet;
    struct in_addr ip_addr;

    handle_ip_segment(ip_header->protocol, ip_header->length - ip_header->ihl,
                      packet + ip_header->ihl);
    printf("Source: ");
    ip_addr.s_addr = ip_header->source_address;
    printf("%s\n", inet_ntoa(ip_addr));
    printf("Destination: ");
    ip_addr.s_addr = ip_header->destination_address;
    printf("%s\n", inet_ntoa(ip_addr));
    return true;
}