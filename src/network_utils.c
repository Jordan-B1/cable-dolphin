#include "network_utils.h"

uint32_t bytes_to_uint32(const uint8_t bytes[4]) {
    return bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3];
}