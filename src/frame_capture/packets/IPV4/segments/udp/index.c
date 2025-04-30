#include "frame_capture/packets/IPV4/segments/udp/udp.h"
#include "utils.h"

static bool fill_udp_header(const uint8_t *packet, udp_header_t *header) {
  SAFE(memcpy(header, packet, sizeof(udp_header_t)));

  header->port_source = ntohs(header->port_source);
  header->port_destination = ntohs(header->port_destination);
  header->length = ntohs(header->length);
  header->checksum = ntohs(header->checksum);
  return true;
}

bool display_udp_packet_info(const uint8_t *packet, [[maybe_unused]] const size_t packet_len,
                             output_buffer_t *output_buffer) {
  udp_header_t header;

  SAFE(packet);
  SAFE(fill_udp_header(packet, &header));
  write_buffer(output_buffer, "Source port: %u\n", header.port_source);
  write_buffer(output_buffer, "Destination port: %u\n",
               header.port_destination);
  write_buffer(output_buffer, "Segment len: %u\n", header.length);
  return true;
}