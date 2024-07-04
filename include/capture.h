#ifndef __CAPTURE_H__
#define __CAPTURE_H__

#include <stdbool.h>
#include <pcap/pcap.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <net/ethernet.h>

bool launch_loop_capture(char *device_name);

#endif // __CAPTURE_H__
