#include "frame_capture/packets/IPV4/ipv4.h"

bool handle_ip_segment(const uint8_t protocol, const uint8_t *packet)
{
    for (int i = 0; i < NB_HANDLED_IP_SEGMENTS; i++) {
        if (protocol == handled_ip_segment[i].p_value) {
            printf("Protocol: %s\n", handled_ip_segment[i].display_name);
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

    // for (int i = 0; i < NB_HANDLED_IP_SEGMENTS; i++) {
    //     if (ip_header->protocol == handled_ip_segment[i].p_value) {
    //         printf("Protocol: %s\n", handled_ip_segment[i].display_name);
    //         break;
    //     }
    //     if (i == NB_HANDLED_IP_SEGMENTS - 1 &&
    //         ip_header->protocol != handled_ip_segment[i].p_value) {
    //         printf("Protocol not handled yet...\n");
    //     }
    // }
    handle_ip_segment(ip_header->protocol, packet + sizeof(const ipv4_header_t));
    printf("Source: ");
    ip_addr.s_addr = ip_header->source_address;
    printf("%s\n", inet_ntoa(ip_addr));
    printf("Destination: ");
    ip_addr.s_addr = ip_header->destination_address;
    printf("%s\n", inet_ntoa(ip_addr));
    return true;
}