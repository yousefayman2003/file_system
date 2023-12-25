#include "dir.h"
void create_root(Dir **root)
{
	*root = malloc(sizeof(Dir));
	
	(*root)->name = "root";
	(*root)->parent = NULL;
	(*root)->size = 0;
	(*root)->dir_permissions = "drwxrwxrwx";
	(*root)->files = NULL;
	(*root)->subdirs = NULL;
	(*root)->number_of_files = 0;

	(*root)->number_of_sub_dirs = 0;
	(*root)->creation_time = time(NULL);
	(*root)->last_modification_time = time(NULL);
	
	current_node->current_dir = *root;
}

void get_back()
{
	if (!current_node->current_file)
	{
		current_node->current_dir = current_node->current_dir->parent;
		current_node->current_file = NULL;
	}
	else if (!current_node->current_dir)
		current_node->current_dir = current_node->current_dir->parent;
	else
		printf("your are already in the root");
}
void go_to_dir(Dir *dir)
{
	int i;
	int found = 0;

	for (i = 0; i < current_node->current_dir->number_of_sub_dirs; i++)
	{
		if (current_node->current_dir->subdirs[i] == dir)
		{
			found = 1;
			current_node->current_dir = dir;
			return;
		}
	}
	if (found == 0)
                perror("directory not found\n");
}

void go_to_file(File *file)
{
        int i;
        int found = 0;

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
Current* initialize_current_node() {
    Current *node = (Current*)malloc(sizeof(Current));
    if (node != NULL) {
        node->current_dir = NULL;
        node->current_file = NULL;
    }
    return node;
}

void appendFile(Dir *dir, char *fileName) {
    // Check if the files array is NULL
    if (dir->files == NULL) {
        // Allocate memory for the files array
        dir->files = malloc(sizeof(File *));
        if (dir->files == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // Reallocate memory for the files array
        dir->files = realloc(dir->files, (dir->number_of_files + 1) * sizeof(File *));
        if (dir->files == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
    }

    // Allocate memory for the new file
    dir->files[dir->number_of_files] = malloc(sizeof(File));
    if (dir->files[dir->number_of_files] == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the file attributes
    strncpy(dir->files[dir->number_of_files]->name, fileName, MAX_NAME_LENGTH - 1);
    // ... initialize other file attributes

    // Increment the number of files
    dir->number_of_files++;
}

// Function to append a subdirectory to the subdirs array
void appendSubdir(Dir **new_dir)
{

    if (current_node->current_dir->number_of_sub_dirs == 0) {
        current_node->current_dir->first_child = malloc(sizeof(Dir));
        if (current_node->current_dir->subdirs == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
	}
	current_node->current_dir->first_child = *new_dir;
	current_node->current_dir->number_of_sub_dirs++;
    }
    else
    {
	    current_node->current_dir->next_sibling = current_node->current_dir->first_child;
        current_node->current_dir->first_child = *new_dir;
	current_node->current_dir->number_of_sub_dirs++;
}
