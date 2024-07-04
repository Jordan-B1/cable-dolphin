#include "capture.h"
#include "if.h"

int main(int ac, const char const * const *argv) {
    char device_name[IF_NAMESIZE] = {0};

    if (!get_first_running_interface(device_name))
        return 1;

    printf("Network interface: %s\n", device_name);

    if (!launch_loop_capture(device_name)) {
        return 1;
    }
    return 0;
}
