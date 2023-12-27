#include "dir.h"

/**
 * get_chars_after_dot - Retrieves characters after the first dot in a string.
 *
 * @input: The input string to search for the dot.
 * @result: Pointer to store the characters after the dot.
*/
void get_chars_after_dot(char *input, char *result)
{
	char *dot_pos = strchr(input, '.');
	if (dot_pos != NULL) 
		strcpy(result, dot_pos + 1);
	else
		result[0] = '\0'; // If no dot found, set the result as an empty string
}


/**
 * get_id - gets id of a file
 * @file: filename
*/
int get_id(char *file)
{
	char name[MAX_NAME_LENGTH], type[MAX_TYPE_LENGTH];
	char *file_name, *file_type, copy[MAX_NAME_LENGTH];
	int i;

	strcpy(copy, file);
	get_chars_before_dot(file, name);
	get_chars_after_dot(copy, type);
	for (i = 0; i < current_node->current_dir->number_of_files; i++)
        {
                file_name = current_node->current_dir->files[i]->name;
		file_type = current_node->current_dir->files[i]->type;
                if ((strcmp(file_name, name) == 0) && (strcmp(file_type, type) == 0))
                {
                        return (current_node->current_dir->files[i]->id);
                }
	}

	return (-1);

}

/**
 * get_tokens - Splits a string by a specified delimiter and returns an array of tokens.
 *
 * @input: The input string to be tokenized.
 * @num_tokens: Pointer to an integer to store the number of tokens found.
 *
 * Return: An array of tokens obtained from the input string.
 *         Returns NULL if memory allocation fails or no tokens are found.
*/
char **get_tokens(const char *input, int *num_tokens) {
	char *token;
    	char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
	int flag = 1;
    	if (tokens == NULL) {
        	printf("Memory allocation failed!\n");
        	*num_tokens = 0;
        	return NULL;
    	}

    	char *input_copy = strdup(input);
    	if (input_copy == NULL) {
        	printf("Memory allocation failed!\n");
        	*num_tokens = 0;
        	free(tokens);
        	return NULL;
    	}

    	token = strtok(input_copy, "/");
    	*num_tokens = 0;
    	while (token != NULL) {
		if (flag == 1)
		{
			flag = 0;
			continue;
		}
        	tokens[*num_tokens] = strdup(token);
        	(*num_tokens)++;
        	token = strtok(NULL, "/");
    	}
    	free(input_copy);
    	return tokens;
}

/**
 * move_file - moves or copies a file to a specific location
 * @id: file id
 * @location: location to move to
 * @delete: 1 to move file, 0 to copy
*/
void move_file(int id, char *location, int delete)
{
	File *file;
	Dir *prev_curr = current_node->current_dir;
	char **tokens, *dir_name;
	int num_tokens, i, j, found = 0;
	if (id == -1)
	{
		printf("Error: File not found\n");
		return;
	}
	file = get_file(id);
	tokens = get_tokens(location, &num_tokens);
	
	/* Get back to root node */
	while (current_node->current_dir->parent != NULL)
		current_node->current_dir = current_node->current_dir->parent;	

	for (i = 1; i < num_tokens; i++)
	{
		for (j = 0; j < current_node->current_dir->number_of_sub_dirs; j++)
        	{
                	dir_name = current_node->current_dir->subdirs[j]->name;
			if (strcmp(dir_name, tokens[i]) == 0)
			{
				current_node->current_dir = current_node->current_dir->subdirs[j];
				found = 1;
				break;
			}
			found = 0;
        	}
		if (found == 0)
			break;
	}
	if (found == 1)
		appendFile(file);
	else
		printf("Error: Path not found.\n");
	current_node->current_dir = prev_curr;
	
	/*if (delete == 1)
		delete_file(id);*/
}
