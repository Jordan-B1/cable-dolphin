#include "frame_capture/packets/IP/ip.h"

bool handle_ip_packet(const u_int8_t *packet) {
    const ipv4_header_t *ip_header =
        (ipv4_header_t *)packet +
        sizeof(struct ether_header); // We skip the ether_packet header
    struct in_addr ip_addr;

    for (int i = 0; i < NB_HANDLED_IP_SEGMENTS; i++) {
        if (ip_header->protocol == handled_ip_segment[i].p_value) {
            printf("Protocol: %s\n", handled_ip_segment[i].display_name);
            break;
        }
        if (i == NB_HANDLED_IP_SEGMENTS -1 && ip_header->protocol != handled_ip_segment[i].p_value) {
            printf("Protocol not handled yet...\n");
        }
    }
    printf("Source: ");
    ip_addr.s_addr = ip_header->source_address;
    printf("%s", inet_ntoa(ip_addr));
    putchar(10);
    printf("Destination: ");
    ip_addr.s_addr = ip_header->destination_address;
    printf("%s", inet_ntoa(ip_addr));
    putchar(10);
    return true;
}