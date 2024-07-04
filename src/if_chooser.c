#include "if.h"

bool get_first_running_interface(char buffer[IF_NAMESIZE]) 
{
    struct ifaddrs *ifaddr_head;
    const char *result_buffer = NULL;

    if (getifaddrs(&ifaddr_head) < 0) {
        perror("can't access network interfaces");
        return false;
    }
    else {
        static const int active_mask = (IFF_RUNNING | IFF_UP | IFF_BROADCAST);
        for (struct ifaddrs *ifaddr = ifaddr_head; ifaddr; ifaddr = ifaddr->ifa_next) {
            if (ifaddr->ifa_addr == NULL)
                continue;
            if ((ifaddr->ifa_flags & active_mask) == active_mask)  {
                result_buffer = ifaddr->ifa_name;
                break;
            }
        }
    }
    if (result_buffer)
        strcpy(buffer, result_buffer);
    return result_buffer != NULL;
}
