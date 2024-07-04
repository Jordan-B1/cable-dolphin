#include "capture.h"
#include "utils.h"

static void display_packet(u_char *_, const struct pcap_pkthdr *header,
                           const u_char *packet) {
    struct ether_header *eth_header;

    eth_header = (struct ether_header *)packet; // which is 14 bytes
    printf("caplen : %d\n", header->caplen);
    printf("len: %d\n", header->len);
    printf("Packet type: ");
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        printf("IP\n");
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        printf("ARP\n");
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_REVARP) {
        printf("Reverse ARP\n");
    }
    for (int i = 0; i < header->caplen; i++) {
        printf("%u ", packet[i]);
    }
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