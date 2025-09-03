#include "cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chararr.h"
#include "str.h"

struct Command* cli_commands = nullptr;
size_t cli_commands_c = 0;

struct Flag* cli_flags = nullptr;
size_t cli_flags_c = 0;

int cli_argc;
char** cli_args = {};

void cli_init(int argc, char* sys_argv[]) {
    cli_argc = argc;
    cli_args = malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; i++) {
        cli_args[i] = strdup(sys_argv[i]);
    }
    if (argc > 0) { // Shift args to remove the path thingy
        if (strchr(sys_argv[0], '/') || strchr(sys_argv[0], '\\')) {
            for (int i = 1; i < argc; i++) {
                cli_args[i - 1] = sys_argv[i];
            }
            cli_args[argc - 1] = nullptr;
            cli_argc--;
        }
    }
}

bool cli_check_init() {
    if (cli_argc != 0) {
        return true;
    }
    printf("No commands provided.\nAvailable:\n");
    for (int i = 0; i < cli_commands_c; i++) {
        struct Command command = cli_commands[i];
        printf("\t%s - %s\n", command.name, command.description);
    }
    printf("Flags:\n");
    for (int i = 0; i < cli_flags_c; i++) {
        struct Flag flag = cli_flags[i];
        printf("\t--%s - %s\n", flag.name, flag.description);
    }
    return false;
}

void cli_register_command(const char* name, const char* description) {
    struct Command* new = realloc(cli_commands, (cli_commands_c + 1) * sizeof(struct Command));
    if (new == nullptr) {
        return;
    }

    cli_commands = new;
    cli_commands[cli_commands_c].name = strdup(name);
    cli_commands[cli_commands_c].description = strdup(description);
    cli_commands_c += 1;
}

void cli_register_flag(const char* name, const char* description) {
    struct Flag* new = realloc(cli_flags, (cli_flags_c + 1) * sizeof(struct Flag));
    if (new == nullptr) {
        return;
    }

    cli_flags = new;
    cli_flags[cli_flags_c].name = strdup(name);
    cli_flags[cli_flags_c].description = strdup(description);
    cli_flags_c += 1;
}

struct CommandResult cli_get_command(const char* name) {
    struct CommandResult result = {nullptr, false };
    if (cli_argc == 0) {
        return result;
    }
    if (strcmp(cli_args[0], name) == 0) {
        if (cli_args[0] == nullptr) {
            printf("cli_args[1] is null");
            return result;
        }
        result.arg0 = cli_args[1];
        result.ok = true;
        return result;
    }
    return result;
}

bool cli_get_flag(const char* name) {
    char* target = malloc(sizeof(char) * 2 + sizeof(name) + 1);
    target[0] = '-';
    target[1] = '-';
    target[(sizeof(char) * 2) + sizeof(*name) + 1] = '\0';
    memcpy(target + sizeof(char) * 2, name, sizeof(name));

    for (int i = 0; i < cli_argc; i++) {
        if (strcmp(cli_args[i], target) == 0) {
            free(target);
            return true;
        }
    }
    free(target);
    return false;
}
