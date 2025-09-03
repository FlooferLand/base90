#ifndef BASE90_CLI_H
#define BASE90_CLI_H

struct Flag {
    const char* name;
    const char* description;
};

struct Command {
    const char* name;
    const char* description;
};

struct CommandResult {
    char* arg0;
    bool ok;
};

void cli_init(int argc, char* args[]);
bool cli_check_init();
void cli_register_command(const char* name, const char* error);
void cli_register_flag(const char* name, const char* description);
struct CommandResult cli_get_command(const char* name);
bool cli_get_flag(const char* name);

#endif