#include <stdlib.h>

void free_strdup(char *str) {
    if (str != NULL) {
        free(str);
    }
}
void free_malloc(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}
