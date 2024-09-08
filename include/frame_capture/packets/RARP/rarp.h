#ifndef __RARP_H__
#define __RARP_H__

#include <netinet/in.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdio.h>

bool handle_rarp_packet(const u_int8_t *packet);

#endif // __RARP_H__
