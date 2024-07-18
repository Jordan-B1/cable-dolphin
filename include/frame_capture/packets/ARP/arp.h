#ifndef __ARP_H__
#define __ARP_H__

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/types.h>

bool handle_arp_packet(const u_int8_t *packet);

#endif // __ARP_H__
