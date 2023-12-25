#include "dir.h"

char *check_name_created(char *name);

/**
 *
 *
 *
 *
 */
void create_dir(Dir **new_dir, char *name)
{
	time_t current_time;

	*new_dir = malloc(sizeof(Dir));
	if (!name)
		(*new_dir)->name = check_name_created("New folder");
	(*new_dir)->name = check_name_created(name);
	(*new_dir)->parent = current_node->current_dir;
	(*new_dir)->size = 0;
	(*new_dir)->dir_permissions = "drwxrwxr-x";
	time(&current_time);
	(*new_dir)->creation_time = current_time;
	(*new_dir)->creation_time = current_time;
	printf("n: %d\n", current_node->current_dir->number_of_sub_dirs);
	appendSubdir(new_dir);
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
	int count = 1;
	char new_dir_name[50];

	Dir *dir_ptr = current_node->current_dir->first_dir;
	while (file_ptr != NULL)
	{
		if (name == file_ptr->name)
		{
			count++;
		}
		dir_ptr = dir_ptr->next_sibiling;
	}
	if (count == 1)
		return (name);
	else
	{
		snprintf(new_dir_name, sizeof(new_dir_name), "%d", count);
		return (strcat(name, new_dir_name));
	}
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
	free(dir);*/
}

/**
 *
 *
 *
 *
 *
 */
void list_dir_content()
{
	Dir *dir_ptr = current_node_current_dir->first_dir;
        File *file_ptr = current_node_current_dir->first_file;

        while (dir_ptr != NULL)
	{
		printf("%s\n", dir_ptr->name);
		dir_ptr = dir_ptr->next_sibiling;
	}
	while (file_ptr != NULL)
        {
                printf("%s\n", file_ptr->name);
                file_ptr = file_ptr->next_sibiling;
        }
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
		printf("%s\t%d\t%ld\t%ld\t%s\n", current_node->current_dir->dir_permissions, current_node->current_dir->size, current_node->current_dir->creation_time, current_node->current_dir->last_modification_time, current_node->current_dir->name);
}

char *search_in_dir(char *searched_name)
{
	Dir *dir_ptr = current_node_current_dir->first_dir;
	File *file_ptr = current_node_current_dir->first_file;
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
