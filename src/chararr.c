#include "chararr.h"
#include <stdlib.h>
#include <string.h>

char* chararr_add(char* target, const char* str) {
    size_t len = strlen(target);
    size_t str_len = strlen(str);
    size_t new_len = len + str_len;

    char* new_data = realloc(target, new_len + 1);
    if (!new_data) {
        return target;
    }

    memcpy(new_data + len, str, str_len + 1);
    return new_data;
}
