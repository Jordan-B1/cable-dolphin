#include "frame_capture/packets/IPV4/segments/udp/udp.h"

static bool fill_udp_header(const uint8_t *packet, udp_header_t *header) {
    SAFE(memcpy(header, packet, sizeof(udp_header_t)));

    header->port_source = ntohs(header->port_source);
    header->port_destination = ntohs(header->port_destination);
    header->length = ntohs(header->length);
    header->checksum = ntohs(header->checksum);
    return true;
}

bool display_udp_packet_info(const uint8_t *packet, const size_t packet_len)
{
    udp_header_t header;

    SAFE(packet);
    SAFE(fill_udp_header(packet, &header));
    printf("Source port: %u\n", header.port_source);
    printf("Destination port: %u\n", header.port_destination);
    printf("Segment len: %u\n", header.length);
}