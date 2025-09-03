#ifndef BASE90_STR_H
#define BASE90_STR_H
#include <stddef.h>

struct String {
    char* data;
    size_t len;
};

struct String str_new();
struct String str_from(const char* chars);
bool str_equals(struct String string, const char* chars);
char** str_split(struct String string, const char* delim);
void str_add(struct String* string, const char* str);

#endif
