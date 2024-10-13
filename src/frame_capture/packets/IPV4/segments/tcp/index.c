#include "frame_capture/packets/IPV4/segments/tcp/tcp.h"

#include "utils.h"

static bool fill_tcp_header(const uint8_t *packet, tcp_header_t *header) {
    SAFE(memcpy(header, packet, sizeof(tcp_header_t)));

    header->sequence_number = ntohl(header->sequence_number);
    header->ack_number = ntohl(header->ack_number);
    header->window = ntohs(header->window);
    header->checksum = ntohs(header->checksum);
    header->urgent_pointer = ntohs(header->urgent_pointer);
    return true;
}

static void display_flags(const uint8_t flags) {
    char flags_name[NB_TCP_FLAGS][4] = {
        "CWR", "ECE", "URG", "ACK", "PSH", "RST", "SYN", "FIN"};

    printf("Flags:");
    for (int i = 0; i < NB_TCP_FLAGS; i++) {
        if ((flags >> i) & 0x01) {
            printf(" %s", flags_name[i]);
        }
    }
    putchar(10);
}

bool display_tcp_packet_info(const uint8_t *packet, const size_t packet_len) {
    tcp_header_t header;

    SAFE(fill_tcp_header(packet, &header));
    printf("Source port: %u\n", header.source_port);
    printf("Destination port: %u\n", header.destination_port);
    printf("Info: SEQ: %u ACK: %u\n", header.sequence_number, header.ack_number);
    display_flags(header.flags);
}