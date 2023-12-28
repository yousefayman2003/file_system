#include "dir.h"

/**
 * get_chars_before_dot - Extracts characters before the dot from a string.
 *
 * @input: The input string to process.
 * @result: Pointer to store the characters before the dot.
 *
 * Return:
 * This function does not return anything as the result is stored in 'result'.
*/
void get_chars_before_dot(char *input, char *result)
{
	/* Find the position of the dot */
	char *dot_pos = strchr(input, '.');
	
	if (dot_pos != NULL)
	{
		int length_before_dot = dot_pos - input;
		strncpy(result, input, length_before_dot);
		result[length_before_dot] = '\0';
	} 
	else
		strcpy(result, input);
}

/**
 * get_file - gets a file with a specific id
 * @id: file id
 * Return: File with that id
*/
File *get_file(int id)
{
	int i, file_id;
        File *file;
	
        for (i = 0; i < current_node->current_dir->number_of_files; i++)
        {
                file_id = current_node->current_dir->files[i]->id;
                if (file_id == id)
                {
                        file = current_node->current_dir->files[i];
			return (file);
                }
        }

        return (NULL);
}

/**
* change_perm_file - changes file permissions
* @id: file id
* @perm: new file permission
*/
void change_perm_file(int id, char *perm)
{
	File *file;
	
	if (id == -1)
	{
		printf("Error: File not found.\n");
		return;
	}
	if (perm == NULL)
	{
		printf("Error Couldn't change permission.\n");
		return;
	}

	file = get_file(id);
	strncpy(file->protection, perm, MAX_PROTECTION_LENGTH - 1);
	file->protection[MAX_PROTECTION_LENGTH - 1] = '\0';
}

/**
 * rename_file - Renames a file
 * @id: file id
 * @new_name: New name for the file
*/
void rename_file(int id, char *new_name)
{
	char *dot;
	File *file;

	if (id == -1 || new_name == NULL)
	{
		printf("Error: Couldn't change name\n");
		return;
	}
	/* get file with that id */
	file = get_file(id);

	if (file == NULL)
	{
		perror("Error: File is not found.");
		return;
	}

	/* Find the last dot in the new name */
        dot = strrchr(new_name, '.');
	if (dot != NULL)
	{
		strncpy(file->name, new_name, dot - new_name);
		file->name[dot - new_name] = '\0';

		strncpy(file->type, dot + 1, sizeof(file->type) - 1);
		file->type[sizeof(file->type) - 1] = '\0';
	}
	else
	{
		strncpy(file->name, new_name, sizeof(file->name) - 1);
		file->name[sizeof(file->name) - 1] = '\0';

		file->type[0] = '\0';
	}

}

/**
 * appendFile - Adds a new file to the current directory.
 * @new_file: Pointer to the new file to be appended.
*/
void appendFile(File *new_file)
{
        char *parent_path;

        if (current_node->current_dir->files == NULL)
        {
                current_node->current_dir->files = malloc(INITIAL_FILE_SPACE * sizeof(File *));
                if (current_node->current_dir->files == NULL)
                {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                static int max_files = INITIAL_FILE_SPACE;

                if (current_node->current_dir->number_of_files >= max_files)
                {
                        /* Reallocate memory for the files array */
                        max_files *= 2;
                        current_node->current_dir->files = realloc(current_node->current_dir->files, max_files * sizeof(File *));
                        if (current_node->current_dir->files == NULL)
                        {
                                fprintf(stderr, "Memory allocation error\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
        /* Allocate memory for the new file */
        current_node->current_dir->files[current_node->current_dir->number_of_files] = malloc(sizeof(File));
        if (current_node->current_dir->files[current_node->current_dir->number_of_files] == NULL)
        {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        /* Initialize the subdirectory */
        current_node->current_dir->files[current_node->current_dir->number_of_files] = new_file;
        if (current_node->current_dir->files[current_node->current_dir->number_of_files] == NULL)
        {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        /* set parent */
        current_node->current_dir->files[current_node->current_dir->number_of_files]->parent = current_node->current_dir;

        /* set path */
        parent_path = strdup(current_node->current_dir->path);
        new_file->location = strdup(strcat(strcat(parent_path, "/"), new_file->name));
        free(parent_path);
        /* Increment the number of subdirectories */
        current_node->current_dir->number_of_files++;
}
