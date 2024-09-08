#include "frame_capture/packets/IPV4/segments/udp/udp.h"
#include "utils.h"

bool display_udp_packet_info(const u_int8_t *packet, const size_t packet_len)
{
    SAFE(packet);
    printf("Protocol: UDP\nInfo: Not implemented yet...\n");
}