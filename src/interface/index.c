#include "interface.h"

static int request_device(pcap_if_t *devices) {
    int index = 0;
    char *user_input = NULL;
    size_t user_index = 0;

    printf("> Choose a device:\n\n");

    for (pcap_if_t *tmp = devices; tmp != NULL; tmp = tmp->next) {
        printf("%s: %s [%d]\n", tmp->name, tmp->description ? tmp->description : "", index);
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
    char *interface = NULL;
    char errbuf[PCAP_ERRBUF_SIZE] = {0};
    pcap_if_t *devices = NULL;
    int status = pcap_findalldevs(&devices, errbuf);
    int index = 0;

    if (status != 0 && errbuf) {
        fprintf(stderr, "%s\n", errbuf);
        return NULL;
    } else if (status != 0) {
        fprintf(stderr, "Something went wrong...\n");
        return NULL;
    }
    index = request_device(devices);
    for (int i = 0; i < index; i++, devices = devices->next);
    return devices->name;
}