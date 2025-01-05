#include "frame_capture/capture.h"
#include "utils.h"
#include "write.h"

typedef struct handling_arg {
  const struct pcap_pkthdr *header;
  const uint8_t *packet;
  pthread_mutex_t *lock;
} handling_arg_t;

void *handling(void *arg) {

  handling_arg_t *param = (handling_arg_t *)arg;
  output_buffer_t buffer = {0};
  struct ether_header *eth_header;

  eth_header = (struct ether_header *)param->packet; // which is 14 bytes
  write_buffer(&buffer, "Timestamp: %ld\ncaplen: %d\nlen: %d\nPacket type: ",
               param->header->ts.tv_sec, param->header->caplen,
               param->header->len);
  for (size_t i = 0; i < NB_PACKET_HANDLED; i++) {
    if (handled_packets[i].type == ntohs(eth_header->ether_type)) {
      write_buffer(&buffer, "%s\n", handled_packets[i].display_name);
      handled_packets[i].handler(param->packet + sizeof(struct ether_header),
                                 &buffer);

      break;
    }
    if (i == NB_PACKET_HANDLED - 1) {
      memset(buffer.buffer, 0, BASE_OUTPUT_BUFFER_SIZE);
      sprintf(buffer.buffer, "not handled packet type [%d]...\n",
              handled_packets[i].type);
      safe_write(buffer.buffer, BASE_OUTPUT_BUFFER_SIZE, 2, param->lock);
      return NULL;
    } 
  }
      write_buffer(&buffer, "\n===\n");
      safe_write(buffer.buffer, buffer.cursor, 1, param->lock);
  return NULL;
}

/*static void display_packet(uint8_t *_, const struct pcap_pkthdr *header,
                           const uint8_t *packet) {
    struct ether_header *eth_header;
    // zlog_buf_t *log_buff = zlog_buf_new(10, 100, "");
    static pthread_mutex_t lock;
    pthread_t thread_id;
    char output[BASE_OUTPUT_BUFFER_SIZE] = {0};

    eth_header = (struct ether_header *)packet; // which is 14 bytes
    sprintf(output, "Timestamp: %ld\ncaplen: %d\nlen: %d\nPacket type: ",
            header->ts.tv_sec, header->caplen, header->len);
    // printf("Timestamp: %ld\n", header->ts.tv_sec);
    // printf("caplen : %d\n", header->caplen);
    // printf("len: %d\n", header->len);
    // printf("Packet type: ");
    // zlog_buf_append(log_buff, output, strlen(output));
    safe_write(output, BASE_OUTPUT_BUFFER_SIZE, 1, &lock);
    // printf("%s", output);
    for (int i = 0; i < NB_PACKET_HANDLED; i++) {
        if (handled_packets[i].type == ntohs(eth_header->ether_type)) {
            // printf("%s\n", handled_packets[i].display_name);
            // memset(output, 0, BASE_OUTPUT_BUFFER_SIZE);
            // snprintf(output, "not handled packet type [%d]...\n",
            // handled_packets[i].type);
            safe_write(handled_packets[i].display_name, 25, 1, &lock);
            safe_write("\n", 1, 1, &lock);
            handled_packets[i].handler(packet + sizeof(struct ether_header));
            break;
        }
        if (i == NB_PACKET_HANDLED - 1) {
            memset(output, 0, BASE_OUTPUT_BUFFER_SIZE);
            snprintf(output, "not handled packet type [%d]...\n",
                     handled_packets[i].type);
            safe_write(output, BASE_OUTPUT_BUFFER_SIZE, 1, &lock);
            // printf("not handled packet type [%d]...\n",
            // handled_packets[i].type);
        }
    }
    safe_write("\n===\n", 5, 1, &lock);
}
*/

static void display_packet(uint8_t *_, const struct pcap_pkthdr *header,
                           const uint8_t *packet) {
  static pthread_mutex_t lock;
  pthread_t thread_id;
  handling_arg_t param = {.header = header, .lock = &lock, .packet = packet};
  pthread_create(&thread_id, NULL, handling, &param);
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
  return true;
}