#include "helper.h"
#include "file.h"
#include "dir.h"

/**
 * help - Displays available commands and their usage.
*/
void help()
{
	printf("Allowed commands: `help`, `touch`\n \
		`read`, `write`, `chmod`, `info`, `rename`\n");
	printf("==============================================\n\n");
	printf("help:  show available command and explain them\n");
	printf("touch:  create an empty file.\nUsage: touch (filename).\n\n");
	printf("read:  reads content of a file.\nUsage: read (filename).\n\n");
	printf("write: write content to a file.\nUsage: write (filename) (content)\n\n");
	printf("chmod: changes permission of a file.\nUsage: chmod (filename)\n\n");
	printf("info: display information about a file.\nUsage: info (filename)\n\n");
	printf("rename: renames a file.\nUsage: rename (filename)\n\n");
}

/**
 * parse_command - Parses the input command and its arguments.
 * @input: The input string to parse.
 * @command: Pointer to store the parsed command.
 * @args: Array to store the parsed arguments.
 * @numArgs: Pointer to an integer to store the number of arguments parsed.
 *
*/
void parse_command(char *input, char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH], int *numArgs)
{
        /* Tokenize the input string based on space delimiter */
        char *token = strtok(input, " ");
        int argCount = 0;

        if (token != NULL)
	{
		/* Store the command */
                strcpy(command, token);
                argCount++;
		
		/* Move to the next token */
                token = strtok(NULL, " ");

                while (token != NULL && argCount < MAX_TOTAL_ARGS)
		{
			/* Store the arguments */
                        strcpy(args[argCount - 1], token);
                        argCount++;
                        token = strtok(NULL, " ");
                }
        }

        *numArgs = argCount - 1;
}

/**
 * handle_command - Handles the execution of the given command with arguments.
 * @command: The command to execute.
 * @args: Array of arguments for the command.
 *
 * Return:
 *  - Returns 1 if the command is 'quit'.
 *  - Returns 0 if the command is 'help' and displays available commands.
 *  - Otherwise, returns -1 indicating an unsupported or unimplemented command.
*/
int handle_command(char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH])
{
	int status = -1;

	if (strcmp(command, "quit") == 0)
		status = 1;
	if (strcmp(command, "help") == 0)
	{
		help();
		status = 0;
	}
	/*
	else if (strcmp(command, "touch") == 0)
	{
		create_file(args[0]);
		status = 0;
	}
	else if (strcmp(command, "rename") == 0)
	{
		rename_file(args[0], args[1]);
		status = 0;
	}
	else if (strcmp(command, "chmod") == 0)
	{
		change_perm_file(args[0], args[1]);
		status = 0;
	}
	else if (strcmp(command, "write") == 0)
	{
		write_file(args[0], args[1]);
		status = 0;
	}
	else if (strcmp(comand, "read") == 0)
	{
		read_file(args[0]);
		status = 0;
	}
	else if (strcmp(command, "info") == 0)
	{
		check_info_file(args[0]);
		status = 0;
	}
	else if (strcmp(command, "mkdir") == 0)
	{
		create_dir(args);
		status = 0;
	}
	*/
	return (status);
}
