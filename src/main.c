#include "frame_capture/capture.h"
#include "interface.h"

int main() {
    char *interface = set_interface(); //wlp0s20f3
    printf("> Interface %s: ", interface);
    if (!interface || !launch_loop_capture(interface)) {
        return 1;
    }
    return 0;
}