#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "utils.h"
#include <getopt.h>
#include <pcap/pcap.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *program_short_options = "f:i:";

static const struct option program_long_options[] = {
        {.name = "filter", .has_arg = required_argument, .flag = 0, .val = 'f'},
        {.name = "interface",
         .has_arg = required_argument,
         .flag = 0,
         .val = 'i'},
        {.name = 0, .has_arg = 0, .flag = 0, .val = 0}};

static const char *allowed_filters[5] = {"tcp", "udp", "ipv4", "ipv6", "arp"};

typedef struct program_config_s {
    char *interface;
    char *filters[5];
} program_config_t;

char *set_interface();
void apply_program_config(int ac, char **av, program_config_t *config);

#endif // __INTERFACE_H__
