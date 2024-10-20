#include "2D_array.h"

int find_index(const void *data, const void **tab) {
    for (int i = 0; tab[i]; i++) {
        if (data == tab[i]) {
            return i;
        }
    }
    return -1;
}

int push_in(void *data, void **tab, bool allow_dup) {
    int free_index = find_index(NULL, (const void **)tab);
    int current_index = allow_dup ? -1 : find_index(data, (const void **)tab);

    if (current_index != -1) {
        return current_index;
    }
    tab[free_index] = data;
}

void free_tab(void **tab) {
    for (int i = 0; tab[i]; i++) {
        free(tab[i]);
    }
    free(tab);
}