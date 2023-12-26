/**#include "file.h"
*/

#include "dir.h"
/**
* change_perm_file - changes file permissions
* @file: given file
* @perm: new file permission
*/
void change_perm_file(File *file, char *perm)
{
	if (file == NULL || perm == NULL)
	{
		perror("Error Couldn't change permission");
		return;
	}
	strncpy(file->protection, perm, MAX_PROTECTION_LENGTH - 1);
	file->protection[MAX_PROTECTION_LENGTH - 1] = '\0';
}

/**
 * rename_file - Renames a file
 * @file: Pointer to the file
 * @new_name: New name for the file
 */
void rename_file(File *file, char *new_name)
{
	if (file == NULL || new_name == NULL)
	{
	perror("Error: Couldn't change name");
	return;
	}

	/* Find the last dot in the new name */
	char *dot = strrchr(new_name, '.');

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

void appendFile(File *new_file)
{
        if (current_node->current_dir->files == NULL)
        {
                current_node->current_dir->files = malloc(sizeof(File *));
                if (current_node->current_dir->files == NULL)
                {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                if (current_node->current_dir->number_of_sub_dirs == (sizeof(current_node->current_dir->files) / sizeof(File *)))
                {
                        /* Reallocate memory for the subdirs array */
                        current_node->current_dir->files = realloc(current_node->current_dir->files, (current_node->current_dir->number_of_files) * 3 * sizeof(File *));
                        if (current_node->current_dir->files == NULL)
                        {
                                fprintf(stderr, "Memory allocation error\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
        /* Allocate memory for the new subdirectory */
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

        /* Increment the number of subdirectories */
        current_node->current_dir->number_of_files++;
}
