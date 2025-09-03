#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base90.h"
#include "cli.h"

bool cli_clean = false;

int main(const int argc, char* args[]) {
    cli_init(argc, args);
    cli_register_command("get", "Example: Use `get 62927` to get the characters for 'owo'");
    cli_register_command("find", "Example: Use `find owo` to find the index for 'owo'");
    cli_register_command("get_charset", "Gets the character set");
    cli_register_flag("clean", "Removes user-facing text, recommended if you're using this as a CLI app.");
    if (!cli_check_init()) {
        return -1;
    }
    base90_init();

    // Flags
    cli_clean = cli_get_flag("clean");

    // Get command
    struct CommandResult get = cli_get_command("get");
    if (get.ok) {
        char* info_ptr;
        const int arg0 = strtol(get.arg0, &info_ptr, 10);
        if (info_ptr == get.arg0) {
            printf("'%s' is not a valid number.\n", get.arg0);
            return -1;
        }
        if (*info_ptr != '\0') {
            printf("Invalid character '%c' \n", *info_ptr);
            return -1;
        }

        char* found = base90_get_index(arg0);
        if (cli_clean) {
            printf("%s", found);
        } else {
            printf("Index for '%s' is %s", get.arg0, found);
        }
        return 0;
    }

    // Find command
    struct CommandResult find = cli_get_command("find");
    if (find.ok) {
        if (cli_clean) {
            const int found = base90_find(find.arg0);
            printf("%d\n", found);
        } else {
            if (strlen(find.arg0) > 3) {
                printf("Finding the index for '%s' (this might take a while for long strings)\n", find.arg0);
            }
            const int found = base90_find(find.arg0);
            printf("find: '%s' is %d\n", find.arg0, found);
        }
        return 0;
    }

    // Get charset command
    struct CommandResult get_charset = cli_get_command("get_charset");
    if (get_charset.ok) {
        printf("%s", base90_get_charset());
        return 0;
    }

    return 0;
}
