#include "file.h"
#include "helper.h"

int main(void)
{
        char input[100];
        char command[MAX_COMMAND_LENGTH];
        char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH];
        int num_args = 0, status = 0;

	
	while (1)
	{
        	printf("Enter command and arguments: ");
        	fgets(input, sizeof(input), stdin);

        	/* Remove the newline character from input */
        	input[strcspn(input, "\n")] = '\0';

        	/* Parse the command and arguments */
        	parse_command(input, command, args, &num_args);

		if (num_args == 0 &&
			strcmp(command, "help") != 0 &&
			strcmp(command, "quit") != 0
			)
		{
			printf("Error: Enter right number of arguments.\n");
			continue;
		}
		
		status = handle_command(command, args);

		if (status)
			break;
		else if (status == -1)
		{
			printf("Error: Invalid command.\n")
		}
	}

        return (0);
}
