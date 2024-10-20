#include <stdbool.h>
#include <stdlib.h>

int push_in(void *data, void **tab, bool allow_dup);
int find_index(const void *data, const void **tab);
void free_tab(void **tab);