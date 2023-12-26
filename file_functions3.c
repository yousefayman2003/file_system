#include "dir.h"

void get_chars_after_dot(char *input, char *result)
{
	char *dot_pos = strchr(input, '.');
	if (dot_pos != NULL) 
		strcpy(result, dot_pos + 1);
	else
		result[0] = '\0'; // If no dot found, set the result as an empty string
}


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
