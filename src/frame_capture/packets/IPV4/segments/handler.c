#include "frame_capture/packets/IPV4/ipv4.h"
#include "utils.h"
#include <arpa/inet.h>

bool handle_ip_segment(const uint8_t protocol, size_t packet_len,
                       const uint8_t *packet, output_buffer_t *output_buffer) {
  for (size_t i = 0; i < NB_HANDLED_IP_SEGMENTS; i++) {
    if (protocol == handled_ip_segment[i].p_value) {
      write_buffer(output_buffer, "Protocol: %s\n",
                   handled_ip_segment[i].display_name);
      handled_ip_segment[i].displayer(packet, packet_len, output_buffer);
      return true;
    }
    if (i == NB_HANDLED_IP_SEGMENTS - 1 &&
        protocol != handled_ip_segment[i].p_value) {
      write_buffer(output_buffer, "Protocol not handled yet... [%u]\n",
                   protocol);
      return false;
    }
  }
  return false;
}

static bool fill_ipv4_header(const uint8_t *packet, ipv4_header_t *header) {
  SAFE(memcpy(header, packet, sizeof(ipv4_header_t)));

  header->length = ntohs(header->length);
  header->id = ntohs(header->id);
  header->flags_offset = ntohs(header->flags_offset);
  header->header_checksum = ntohs(header->header_checksum);
  header->source_address = ntohl(header->source_address);
  header->destination_address = ntohl(header->destination_address);
  return true;
}

bool handle_ipv4_packet(const uint8_t *packet, output_buffer_t *output_buffer) {
  ipv4_header_t ip_header;
  struct in_addr ip_addr;

  SAFE(fill_ipv4_header(packet, &ip_header));

  handle_ip_segment(ip_header.protocol,
                    ip_header.length - (ip_header.version_ihl & 0x0F),
                    (packet + (ip_header.version_ihl & 0x0F)), output_buffer);
  write_buffer(output_buffer, "Source: ");
  ip_addr.s_addr = htonl(ip_header.source_address);
  write_buffer(output_buffer, "%s\nDestination: ", inet_ntoa(ip_addr));
  ip_addr.s_addr = htonl(ip_header.destination_address);
  write_buffer(output_buffer, "%s\n", inet_ntoa(ip_addr));
  return true;
}