#include "frame_capture/packets/ARP/arp.h"
#include "network_utils.h"
#include "utils.h"
#include <arpa/inet.h>

static char *display_mac_address(const uint8_t *addr) {
    struct ether_addr et_addr = {.ether_addr_octet = {addr[0], addr[1], addr[2],
                                                      addr[3], addr[4],
                                                      addr[5]}};
    return ether_ntoa(&et_addr);
}

bool handle_arp_packet(const uint8_t *packet, output_buffer_t *output_buffer) {
    struct in_addr ip_addr;
    const arp_packet_t *arp_packet = (const arp_packet_t *)packet;

    if (arp_packet->protocol_address_len != 4 ||
        arp_packet->protocol_type != ntohs(ETHERTYPE_IP)) {
        write_buffer(output_buffer, "Info: not handled ARP packet...\n");
        write_buffer(output_buffer, "proto type: %u -- proto len: %u",
                     arp_packet->protocol_type,
                     arp_packet->protocol_address_len);
        return false;
    }

    write_buffer(output_buffer, "Sender MAC address: %s\n",
                 display_mac_address(packet + 8));
    write_buffer(output_buffer, "Sender MAC address: %s\n",
                 display_mac_address(packet + 18));

    ip_addr.s_addr =
        htonl(bytes_to_uint32(arp_packet->target_protocol_address));
    write_buffer(output_buffer, "Info: Who has %s?", inet_ntoa(ip_addr));
    ip_addr.s_addr =
        htonl(bytes_to_uint32(arp_packet->sender_protocol_address));
    write_buffer(output_buffer, " Tell %s\n", inet_ntoa(ip_addr));
    return true;
}