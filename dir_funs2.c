#include "dir.h"
/**
 * search_in_dir - Searches for a directory or file by name in the current directory.
 * @searched_name: Name to search for.
 *
 * Return: If found, returns the name of the directory or file. Otherwise, returns NULL.
 */
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
	return (NULL);
}

/** 
 * change_dir_permissions - Changes the permissions of the current directory.
 * @permession: New permissions to set.
 *
 * Return: None.
 */
void change_dir_permissions(char *permession)
{
        if (!current_node->current_dir)
                return;
        current_node->current_dir->dir_permissions = strdup(permession);
        current_node->current_dir->last_modification_time = time(NULL);
}
/**
 * make_path - Creates and returns the full path of a directory within the current directory.
 * @dir: Pointer to the Dir structure for which to create the path.
 *
 * Return: A dynamically allocated string representing the full path.
 */
char *make_path(Dir *dir)
{
	char *copy;

	copy = strdup(current_node->current_dir->path);
	return (strcat(strcat(copy, "/"), dir->name));
}
