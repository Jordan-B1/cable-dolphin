#include "capture.h"
#include "utils.h"
#include <sys/types.h>
// #include <tirpc/rpc/types.h>

static bool handle_ip_packet(const u_char *packet) {
    const u_char *ip_header =
        packet + sizeof(struct ether_header); // we skip the ether_packet header
    int packet_size = *ip_header & 15; // The IP packet header size is stored on
                                       // the last 4 bits of the first byte
    u_char protocol = 0;
    struct in_addr ip_addr;

    packet_size *=
        4; // because the size is stored as number of 32bits segments (4 bytes)
    protocol = *(ip_header + 9); // The protocol used is stored in the 9th bytes
    if (protocol == IPPROTO_TCP) {
        printf("This is a TCP protocol\n");
    } else if (protocol == IPPROTO_UDP) {
        printf("This is a UDP protocol\n");
    }
    printf("Source: ");

    for (int i = 0; i < 4; i++) {
        printf("%u.", *(ip_header + 4 + (sizeof(u_char) * i)));
    }
    putchar(10);
    printf("Destination: ");
    for (int i = 0; i < 4; i++) {
        printf("%u.", *(ip_header + 8 + (sizeof(u_char) * i)));
    }
    putchar(10);
}

static void display_packet(u_char *_, const struct pcap_pkthdr *header,
                           const u_char *packet) {
    struct ether_header *eth_header;

    eth_header = (struct ether_header *)packet; // which is 14 bytes
    printf("Timestamp: %ld\n", header->ts.tv_sec);
    printf("caplen : %d\n", header->caplen);
    printf("len: %d\n", header->len);
    printf("Packet type: ");
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        printf("IP\n");
        handle_ip_packet(packet);
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        printf("ARP\n");
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_REVARP) {
        printf("Reverse ARP\n");
    }
    // for (int i = 0; i < header->caplen; i++) {
    //     printf("%u ", packet[i]);
    // }
    puts("\n===\n");
}

static pcap_t *create_handler(char *device_name) {
    char error[PCAP_ERRBUF_SIZE] = {0};
    int activate = 0;
    pcap_t *handler = NULL;

    SAFE(device_name);
    handler = pcap_create(device_name, error);
    PSAFE(device_name, ("%s", error));
    printf("Handler created!\n");
    activate = pcap_activate(handler);
    if (activate < 0) {
        perror("Handler activation failed");
        return NULL;
    } else if (activate > 0) {
        printf("Warning while activating handler %d", activate);
    }
    return handler;
}

bool launch_loop_capture(char *device_name) {
    pcap_t *handler = create_handler(device_name);

    SAFE(handler);
    pcap_loop(handler, 0, display_packet, NULL);
    pcap_close(handler);
}