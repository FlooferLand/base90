#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String str_new() {
    const struct String s = {
        malloc(1),
        0
    };
    if (s.data) {
        s.data[0] = '\0';
    }
    return s;
}

struct String str_from(const char* chars) {
    struct String s = {};
    s.len = strlen(chars);
    s.data = strcpy(malloc(s.len + 1), chars);
    return s;
}

bool str_equals(const struct String string, const char* chars) {
    return strcmp(string.data, chars) == 0;
}

char** str_split(const struct String string, const char* delim) {
    char* copy = malloc(strlen(string.data) + 1);
    if (!copy) return nullptr;
    strcpy(copy, string.data);

    char** tokens = {};
    size_t count = 0;

    char* token = strtok(copy, delim);
    while (token) {
        char** tmp = realloc(tokens, (count + 1) * sizeof(*tokens));
        if (!tmp) {
            free(tokens);
            free(copy);
            return nullptr;
        }
        tokens = tmp;
        tokens[count++] = token;
        token = strtok(nullptr, delim);
    }
    free(copy);
    return tokens;
}

void str_add(struct String* string, const char* str) {
    size_t str_len = strlen(str);
    size_t new_len = string->len + str_len;

    char* new_data = realloc(string->data, new_len + 1);
    if (!new_data) {
        free(new_data);
        return;
    }

    memcpy(new_data + string->len, str, str_len + 1);
    string->data = new_data;
    string->len = new_len;
}