#include "2D_array.h"
#include "interface.h"

char **list_devices() {
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *devices = NULL;
    int nb_device = 0;
    char **devices_name;
    int index = 0;
    int status = pcap_findalldevs(&devices, errbuf);

    if (status != 0) {
        fprintf(stderr, "%s\n", errbuf ? errbuf : "Something went wrong...");
        return NULL;
    }
    for (pcap_if_t *_ = devices; _; _ = _->next)
        nb_device++;
    devices_name = calloc(sizeof(char *), nb_device + 1);
    for (pcap_if_t *_ = devices; _; _ = _->next) {
        devices_name[index] = strdup(_->name);
        index++;
    }
    pcap_freealldevs(devices);
    return devices_name;
}

static int request_device(const pcap_if_t *devices) {
    int index = 0;
    char *user_input = NULL;
    size_t user_index = 0;

    printf("> Choose a device:\n\n");

    for (const pcap_if_t *tmp = devices; tmp != NULL; tmp = tmp->next) {
        printf("%s: %s [%d]\n", tmp->name,
               tmp->description ? tmp->description : "", index);
        index++;
    }
    getline(&user_input, &user_index, stdin);
    user_index = atoi(user_input);
    free(user_input);
    if (user_index >= index || user_index < 0) {
        fprintf(stderr, "Invalid device... Choosing interface 0");
        return 0;
    }
    return (user_index);
}

char *set_interface(void) {
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *devices = NULL;
    int status = pcap_findalldevs(&devices, errbuf);
    int index = 0;

    if (status != 0) {
        fprintf(stderr, "%s\n", errbuf ? errbuf : "Something went wrong...");
        return NULL;
    }
    index = request_device(devices);
    for (int i = 0; i < index; i++, devices = devices->next)
        ;
    return devices->name;
}

static void i_flag(char **devices_name, program_config_t *config) {
    for (int i = 0; devices_name[i]; i++) {
        if (strcmp(devices_name[i], optarg) == 0) {
            config->interface = optarg;
        }
    }
    if (!config) {
        fprintf(stderr, "Invalid interface %s\n", optarg);
    }
}

static void f_flag(program_config_t *config) {
    int index_filter = 0;

    index_filter = find_index(optarg, (const void **)allowed_filters);
    if (index_filter == -1) {
        fprintf(stderr, "Invalid protocol %s\n", optarg);
    }
    push_in(optarg, (void **)config->filters, false);
}

void apply_program_config(int ac, char **av, program_config_t *config) {
    char **devices_name = list_devices();
    int opt_res = 0;

    if (!devices_name)
        return;
    while ((opt_res = getopt_long(ac, av, program_short_options,
                                  program_long_options, NULL)) != -1) {
        switch (opt_res) {
        case 'i':
            i_flag(devices_name, config);
            break;
        case 'f':
            f_flag(config);
            break;
        default:
            fprintf(stderr, "Invalid parameter %c\n", opt_res);
            break;
        }
    }
    free_tab((void **)devices_name);
}