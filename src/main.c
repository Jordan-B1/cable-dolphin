#include "frame_capture/capture.h"
#include "interface.h"

int main(int ac, char **av) {
    program_config_t config = {0};
    char *interface = NULL;
    
    apply_program_config(ac, av, &config);
    interface = config.interface ? config.interface : set_interface(); //wlp0s20f3
    printf("> Interface %s: ", interface);
    if (!interface || !launch_loop_capture(interface)) {
        return 1;
    }
    return 0;
}