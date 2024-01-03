#include "dir.h"

char *check_name_created(char *name);

/** 
 * create_dir - create directory with name.
 * @name: Name of the directory.
 *
 * Return: Directory created.
 */
Dir *create_dir(char *name)
{
	Dir *new_dir;
	time_t current_time;

	new_dir = malloc(sizeof(Dir));
	if (new_dir == NULL)
	{
		perror("memory allocation error");
		exit(EXIT_FAILURE);
	}
	if (name[0] == '\0')
		new_dir->name = check_name_created("New_folder");
	else
		new_dir->name = strdup(check_name_created(name));
	new_dir->size = 0;
	new_dir->dir_permissions = strdup("drwxrwxr-x");
	time(&current_time);
	new_dir->creation_time = current_time;
	new_dir->last_modification_time = current_time;
	new_dir->parent = current_node->current_dir;
        new_dir->path = strdup(make_path(new_dir));
	appendSubdir(&new_dir);
	return (new_dir);
}
/** 
 * check_name_created - Checks if a directory name already exists and appends a number if needed.
 * @name: Name of the directory to be checked.
 *
 * Return: Modified name if duplicates are found, otherwise the original name.
 */
char *check_name_created(char *name)
{
	int i, count = 1;
	char new_dir_name[50], *new_name;
	
	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
	{
		if (strcmp(name, current_node->current_dir->subdirs[i]->name) == 0)
		{
			count++;
		}
	}

	if (count > 1)
	{
		snprintf(new_dir_name, sizeof(new_dir_name), "%d", count);
		// Allocate memory for the new name (original name + count + null terminator)
		new_name = malloc(strlen(name) + strlen(new_dir_name) + 1);
		if (new_name == NULL)
		{
			// Handle memory allocation failure
			return (NULL);
		}

		strcpy(new_name, name);
		strcat(new_name, new_dir_name);
		return (new_name);
	}
	return name;
}

/** 
 * delete_file - Deletes a file from the directory.
 * @file: Pointer to the File structure to be deleted.
 *
 * Return: None.
 */
void delete_file(File *file)
{
        if (file == NULL)
	{
		return;       /* Do nothing if the file is already NULL */
	}

	/* Free dynamically allocated fields */
	if (file->location)
		free(file->location);

	/* Update parent directory's files array */
	if (file->parent != NULL)
	{
		for (int i = 0; i < file->parent->number_of_files; ++i)
		{
			if (file->parent->files[i] == file) {
				/* Shift remaining files to the left */
				for (int j = i; j < file->parent->number_of_files - 1; ++j)
				{
					file->parent->files[j] = file->parent->files[j + 1];
				}
				file->parent->number_of_files--;
				break;
			}
		}
	}
	current_node->current_dir->size -= file->size;
	/* Free the file itself */
	free(file);
}
/** 
 * delete_dir_name - Deletes a directory by name.
 * @dir_name: Name of the directory to be deleted.
 *
 * Return: None.
 */
void delete_dir_name(const char *dir_name)
{
	Dir *dir = NULL;
	
	// Search for the directory by name
	// You may need to specify the directory in which to search, e.g., current_node->current_dir
	// For simplicity, this example assumes you want to search in the root directory.
	for (int i = 0; i < current_node->current_dir->number_of_sub_dirs; ++i)
	{
		if (strcmp(current_node->current_dir->subdirs[i]->name, dir_name) == 0) {
			dir = current_node->current_dir->subdirs[i];
			break;
		}
	}

	// If the directory is found, delete it
	if (dir != NULL)
	{
		// Free the directory and update parent directory
		delete_dir(dir);
	}
	else
	{
		printf("Directory not found: %s\n", dir_name);
	}
}

/** 
 * delete_dir - Recursively deletes a directory and its contents.
 * @dir: Pointer to the Dir structure to be deleted.
 *
 * Return: None.
 */
void delete_dir(Dir *dir)
{
	if (dir == NULL)
	{
		return; // Do nothing if the directory is already NULL
	}

	// Free dynamically allocated fields
	if (dir->name)
		free(dir->name);
	if (dir->path)
		free(dir->path);
	if (dir->dir_permissions)
		free(dir->dir_permissions);

	// Recursively free subdirectories
	for (int i = 0; i < dir->number_of_sub_dirs; ++i)
	{
		delete_dir(dir->subdirs[i]);
		dir->subdirs[i] = NULL;
	}
	free(dir->subdirs);

	// Free files in the directory
	for (int i = 0; i < dir->number_of_files; ++i)
	{
		delete_file(dir->files[i]);
		dir->files[i] = NULL;
	}
	free(dir->files);
	// Update parent directory's subdirectories array
	if (dir->parent != NULL)
	{
		for (int i = 0; i < dir->parent->number_of_sub_dirs; ++i)
		{
			if (dir->parent->subdirs[i] == dir)
			{
				// Shift remaining subdirectories to the left
				for (int j = i; j < dir->parent->number_of_sub_dirs - 1; ++j)
				{
					dir->parent->subdirs[j] = dir->parent->subdirs[j + 1];
				}
				dir->parent->number_of_sub_dirs--;
				break;
			}
		}
	}

	// Free the directory itself
	free(dir);
}

/** 
 * list_dir_content - Lists the contents (subdirectories and files) of the current directory.
 *
 * Return: None.
 */
void list_dir_content()
{
	int i;

	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
	{
		printf("%s/\n", current_node->current_dir->subdirs[i]->name);
	}
	for (i = 0; i < current_node->current_dir->number_of_files; i++)
	{
		printf("%s", current_node->current_dir->files[i]->name);
		if (current_node->current_dir->files[i]->type[0] != '\0')
			printf(".%s\n", current_node->current_dir->files[i]->type);
		else
			printf("\n");
	}
}
/** 
 * dir_info - Displays information about the current directory.
 *
 * Return: None.
 */
void dir_info()
{
	if (current_node->current_dir)
	{
		// Convert creation time to string
		char creation_time_str[30];
		strftime(creation_time_str, sizeof(creation_time_str), "%Y-%m-%d %H:%M:%S", localtime(&current_node->current_dir->creation_time));

		// Convert modification time to string
		char modification_time_str[30];
		strftime(modification_time_str, sizeof(modification_time_str), "%Y-%m-%d %H:%M:%S", localtime(&current_node->current_dir->last_modification_time));

		printf("%s\tsize: %f\tcreation: %s\tmodification: %s\tname: %s\tpath: %s\n", 
				current_node->current_dir->dir_permissions, 
				current_node->current_dir->size, 
				creation_time_str, 
				modification_time_str,
				current_node->current_dir->name,
				current_node->current_dir->path);
	}
	else
		perror("No thing");
}
