#ifndef __IF_H__
#define __IF_H__

#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdbool.h>
#include <stdio.h>

bool get_first_running_interface(char buffer[IF_NAMESIZE]);

#endif // __IF_H__ 