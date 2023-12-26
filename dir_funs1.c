#include "dir.h"

char *check_name_created(char *name);

/**
 *
 *
 *
 *
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
	if (!name)
		new_dir->name = check_name_created("New folder");
	new_dir->name = check_name_created(name);
	new_dir->size = 0;
	new_dir->dir_permissions = "drwxrwxr-x";
	time(&current_time);
	new_dir->creation_time = current_time;
	new_dir->creation_time = current_time;
	printf("n: %d\n", current_node->current_dir->number_of_sub_dirs);
	appendSubdir(new_dir);
	return (new_dir);
}

/**
 *
 *
 *
 *
 *
 *
 *
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
 *
 *
 *
 *
 *
 *
 *
 */
/**void delete_dir(Dir *dir)
{
	File *filePtr = dir->first_file, *nextFile, *subDirPtr, *nextSubDir;
	while (filePtr != NULL) {
		nextFile = filePtr->nextSibling;
		delete_file(filePtr);
		filePtr = nextFile;
	}

	subDirPtr = dir->first_dir;
	while (subDirPtr != NULL)
	{
		nextSubDir = subDirPtr->next_sibling;
		delete_dir(subDirPtr);
		subDirPtr = nextSubDir;
	}
	printf("Deleting directory: %s\n", dir->name);
	free(dir);
}*/
/**	int i, found = 0;
	Dir *dir_ptr = current_node->current_dir->first_dir;

	while (dir_ptr)
	{
		if (dir_ptr == dir)
		{
			found = 1;
			break;
		}
	}
	if (found == 0)
	{
		printf("required file not found in this directory\n");
		return;
	}
	if (dir->name)
		free(dir->name);
	if (dir->dir_permissions)
		free(dir->dir_permissions);
	for (i = 0; i < dir->number_of_files; ++i)
		delete_file(dir->files[i]);
	if (dir->files)
		free(dir->files);

	for (i = 0; i < dir->number_of_sub_dirs; ++i)
		delete_dir(dir->subdirs[i]);

	if (dir->subdirs)
		free(dir->subdirs);
	free(dir);
}*/

/**
 *
 *
 *
 *
 *
 */
void list_dir_content()
{
	int i;

	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
		printf("%s\n", current_node->current_dir->subdirs[i]->name);
	for (i = 0; i < current_node->current_dir->number_of_files; i++)
                printf("%s\n", current_node->current_dir->files[i]->name);
}

/**
 *
 *
 *
 *
 *
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

		printf("%s\t%d\t%s\t%s\t%s\n", 
				current_node->current_dir->dir_permissions, 
				current_node->current_dir->size, 
				creation_time_str, 
				modification_time_str, 
				current_node->current_dir->name);
	}
	else
		perror("No thing");
}

char *search_in_dir(char *searched_name)
{
	int i;

	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
	{
		if (strcmp(current_node->current_dir->subdirs[i]->name, searched_name) == 0)
		{
			printf("%s found here\n", searched_name);
			return (current_node->current_dir->subdirs[i]->name);
		}
	}
	for (i = 0; i < current_node->current_dir->number_of_files; i++)
        {
                if (strcmp(current_node->current_dir->files[i]->name, searched_name) == 0)
		{
			printf("%s found here\n", searched_name);
			return (current_node->current_dir->files[i]->name);
		}
        }
}

/**
 *
 *
 *
 */
void change_dir_permissions(char *permession)
{
	if (!current_node->current_dir)
		return;
	current_node->current_dir->dir_permissions = permession;
	current_node->current_dir->last_modification_time = time(NULL);
}
