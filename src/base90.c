#include "base90.h"
#include "str.h"
#include <stdlib.h>
#include <string.h>

struct String base90_chars = {};

void base90_init() {
    struct String letters = str_from("abcdefghijklmnopqrstuvwxyz");
    struct String numbers = str_from("1234567890");
    struct String special = str_from("`~!@#$%^&*()-=[]{}'\"|\\,.<>/?");

    char* chars = malloc(letters.len + numbers.len + special.len + 1);
    memcpy(chars, letters.data, letters.len);
    memcpy(chars + letters.len, numbers.data, numbers.len);
    memcpy(chars + letters.len + numbers.len, special.data, special.len);

    base90_chars = str_from(chars);
}

char* base90_get_index(int num) {
    int tmp = num;
    int digits = 0;
    while (tmp > 0) {
        tmp = (tmp - 1) / base90_chars.len;
        ++digits;
    }
    char* out = malloc((size_t) digits + 1);
    if (!out) return nullptr;
    out[digits] = '\0';

    for (int i = digits - 1; i >= 0; --i) {
        num -= 1;
        out[i] = base90_chars.data[num % base90_chars.len];
        num /= (int) base90_chars.len;
    }

    return out;
}

int base90_find(char* text) {
    for (int i = 1; true; i++) {
        char* out = base90_get_index(i);
        if (!out) return -1;
        if (strcmp(text, out) == 0) {
            return i;
        }
        free(out);
    }
}
