#include "frame_capture/packets/IP/segments/tcp/tcp.h"

#include "utils.h"

bool display_tcp_packet_info(const u_int8_t *packet, const size_t packet_len)
{
    SAFE(packet);
    printf("Protocol: UDP\nInfo: Not implemented yet...\n");
}