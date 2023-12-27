#include "dir.h"
/**
 * help - Displays available commands and their usage.
*/
void help()
{
	printf("Allowed commands: `help`, `touch`\n \
		`read`, `write`, `chmod`, `info`, `rename`\n");
	printf("=====================================================\n\n");
	printf("help:  show available command and explain them\n\n");
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
        int argCount = 0, i;

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
	args[argCount - 1][0] = '\0';
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
	int status = -1, id;
	
	if (strcmp(command, "quit") == 0)
		status = 1;
	else if (strcmp(command, "help") == 0)
	{
		help();
		status = 0;
	}
	else if (strcmp(command, "ls") == 0)
	{
		list_dir_content();
		status = 0;
	}
	else if (strcmp(command, "mkdir") == 0)
	{
		create_dir(args[0]);
		status = 0;
	}
	else if (strcmp(command, "touch") == 0)
	{
		id = get_id(args[0]);
		create_file(args[0]);
		status = 0;
	}
	
	else if (strcmp(command, "rename") == 0)
	{
		id = get_id(args[0]);
		rename_file(id, args[1]);
		status = 0;
	}
	else if (strcmp(command, "chmod") == 0)
	{
		id = get_id(args[0]);
		change_perm_file(id, args[1]);
		status = 0;
	}
	else if (strcmp(command, "write") == 0)
	{
		id = get_id(args[0]);
		write_file(id, args[1]);
		status = 0;
	}
	else if (strcmp(command, "read") == 0)
	{
		char *content;
		id = get_id(args[0]);
		content = read_file(id);
		if (content != NULL)
		{
			printf("%s\n", content);
		}
		status = 0;
	}
	else if (strcmp(command, "info") == 0)
	{
		id = get_id(args[0]);
		information_file(id);
		status = 0;
	}
	else if (strcmp(command, "delete") == 0)
	{
		id = get_id(args[0]);
		delete_file(id);
		status = 0;
	}
	return (status);
}
