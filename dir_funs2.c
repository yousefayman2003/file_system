#include "dir.h"
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
char *make_path(Dir *dir)
{
	char *copy;

	copy = strdup(current_node->current_dir->path);
	return (strcat(strcat(copy, "/"), dir->name));
}
