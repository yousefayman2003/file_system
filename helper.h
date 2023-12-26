#ifndef HELPER_H
#define HELPER_H


#define MAX_COMMAND_LENGTH 50
#define MAX_ARGS_LENGTH 50
#define MAX_TOTAL_ARGS 10

void help();
void parse_command(char *input, char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH], int *numArgs);
int handle_command(char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH]);
#endif
