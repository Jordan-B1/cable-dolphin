#include "frame_capture/capture.h"
#include "utils.h"
#include "write.h"
#include <stdint.h>

static bool packet_identification(const uint8_t *packet, pthread_mutex_t *lock,
                                  output_buffer_t *buffer) {
    const struct ether_header *eth_header =
        (const struct ether_header *)packet; // which is 14 bytes

    for (size_t i = 0; i < NB_PACKET_HANDLED; i++) {
        if (handled_packets[i].type == ntohs(eth_header->ether_type)) {
            write_buffer(buffer, "%s\n", handled_packets[i].display_name);
            handled_packets[i].handler(packet + sizeof(struct ether_header),
                                       buffer);
            return true;
        }
        if (i == NB_PACKET_HANDLED - 1) {
            memset(buffer->buffer, 0, BASE_OUTPUT_BUFFER_SIZE);
            sprintf(buffer->buffer, "not handled packet type [%d]...\n",
                    handled_packets[i].type);
            safe_write(buffer->buffer, BASE_OUTPUT_BUFFER_SIZE, 2, lock);
            return false;
        }
    }
    return false;
}

static void *eth_frame_handler(void *arg) {
    eth_frame_handler_arg_t *param = (eth_frame_handler_arg_t *)arg;
    output_buffer_t buffer = {0};

    write_buffer(&buffer, "Timestamp: %ld\ncaplen: %d\nlen: %d\nPacket type: ",
                 param->header->ts.tv_sec, param->header->caplen,
                 param->header->len);
    if (packet_identification(param->packet, param->lock, &buffer)) {
        write_buffer(&buffer, "\n===\n");
        safe_write(buffer.buffer, buffer.cursor, 1, param->lock);
    }
    return NULL;
}

static void display_packet(__attribute__((unused)) uint8_t *_, const struct pcap_pkthdr *header,
                           const uint8_t *packet) {
    static pthread_mutex_t lock;
    pthread_t thread_id;
    eth_frame_handler_arg_t param = {
        .header = header, .lock = &lock, .packet = packet};
    pthread_create(&thread_id, NULL, eth_frame_handler, &param);
}

static pcap_t *create_handler(const char *device_name) {
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

bool launch_loop_capture(const char *device_name) {
    pcap_t *handler = create_handler(device_name);

    SAFE(handler);
    pcap_loop(handler, 0, display_packet, NULL);
    pcap_close(handler);
    return true;
}