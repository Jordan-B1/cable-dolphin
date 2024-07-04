#include "capture.h"

int main() {
    if (!launch_loop_capture("wlp0s20f3")) {
        return 1;
    }
    return 0;
}