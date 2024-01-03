#include "dir.h"
/** 
 * create_root - Creates the root directory and initializes its attributes.
 * @root: Pointer to the Dir structure for the root directory.
 *
 * Return: None.
 */
void create_root(Dir *root)
{
	root = malloc(sizeof(Dir));
	if (root == NULL)
	{
		perror("memory allocation error");
		exit(EXIT_FAILURE);
	}
	
	root->name = "root";
	root->parent = NULL;
	root->path = strdup("/root");
	root->size = 0;
	root->dir_permissions = "drwxrwxrwx";
	root->files = NULL;
	root->subdirs = NULL;
	root->number_of_files = 0;

	root->number_of_sub_dirs = 0;
	root->creation_time = time(NULL);
	root->last_modification_time = time(NULL);
	
	current_node->current_dir = root;
}
/** 
 * get_back - Moves back to the parent directory or exits if already in the root.
 *
 * Return: None.
 */
void get_back()
{
	if (current_node->current_file != NULL)
	{
		/* current_node->current_dir = current_node->current_file->parent; */
		current_node->current_file = NULL;
	}
	else if (current_node->current_dir->parent == NULL)
		printf("/root\n");
	else
		current_node->current_dir = current_node->current_dir->parent;
}
/** 
 * go_to_dir - Moves to the specified subdirectory within the current directory.
 * @name: Name of the target subdirectory.
 *
 * Return: None.
 */
void go_to_dir(char *name)
{
	int i;
	int found = 0;

	if (current_node->current_file != NULL)
        {
                printf("Command not recognized, you are already in a file\n");
                return;
        }
	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
	{
		if (strcmp(current_node->current_dir->subdirs[i]->name, name) == 0)
		{
			found = 1;
			current_node->current_dir = current_node->current_dir->subdirs[i];
			return;
		}
	}
	if (found == 0)
                perror("directory not found\n");
}
/** 
 * go_to_file - Moves to the specified file within the current directory.
 * @file: Pointer to the File structure of the target file.
 *
 * Return: None.
 */
void go_to_file(File *file)
{
        int i;
        int found = 0;

	if (current_node->current_file != NULL)
	{
		printf("Command no recognized, you are already in another file\n");
		return;
	}
        for (i = 0; i < current_node->current_dir->number_of_files; i++)
        {
                if (current_node->current_dir->files[i] == file)
                {
                        found = 1;
                        current_node->current_file = file;
                        return;
                }
        }
	if (found == 0)
		perror("file not found\n");
}
/** 
 * initialize_current_node - Initializes the current node structure.
 *
 * Return: Pointer to the initialized Current structure.
 */
Current *initialize_current_node()
{
	Current *node = (Current*)malloc(sizeof(Current));
	if (node != NULL) {
		node->current_dir = NULL;
		node->current_file = NULL;
	}
	return node;
}
/**
 * appendSubdir - Appends a new subdirectory to the current directory.
 * @new_dir: Pointer to the Dir structure of the new subdirectory.
 *
 * Return: None.
 */
void appendSubdir(Dir **new_dir)
{
        if (current_node->current_dir->subdirs == NULL)
        {
                current_node->current_dir->subdirs = malloc(INITIAL_FILE_SPACE * sizeof(Dir *));
                if (current_node->current_dir->subdirs == NULL)
                {
                        fprintf(stderr, "Memory allocation error\n");
                        exit(EXIT_FAILURE);
                }
        }
        else
        {
                static int max_files = INITIAL_FILE_SPACE;

                if (current_node->current_dir->number_of_sub_dirs >= max_files)
                {
                        /* Reallocate memory for the files array */
                        max_files *= 2;
                        current_node->current_dir->subdirs = realloc(current_node->current_dir->subdirs, max_files * sizeof(Dir *));
                        if (current_node->current_dir->subdirs == NULL)
                        {
                                fprintf(stderr, "Memory allocation error\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
        /* Allocate memory for the new file */
        current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs] = malloc(sizeof(Dir));
        if (current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs] == NULL)
        {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        /* Initialize the subdirectory */
        current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs] = *new_dir;
        if (current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs] == NULL)
        {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
        }

        /* Increment the number of subdirectories */
        current_node->current_dir->number_of_sub_dirs++;
}
