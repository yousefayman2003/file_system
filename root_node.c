#include "dir.h"
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


void get_to_root()
{

	current_node->current_dir = &root;
}

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

Current *initialize_current_node()
{
	Current *node = (Current*)malloc(sizeof(Current));
	if (node != NULL) {
		node->current_dir = NULL;
		node->current_file = NULL;
	}
	return node;
}

void appendSubdir(Dir **new_dir)
{
	if (current_node->current_dir->subdirs == NULL)
	{
		current_node->current_dir->subdirs = malloc(sizeof(Dir *));
		if (current_node->current_dir->subdirs == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/**if (current_node->current_dir->number_of_sub_dirs == (sizeof(current_node->current_dir->subdirs) / sizeof(Dir *)))
		{*/
			/* Reallocate memory for the subdirs array */
		current_node->current_dir->subdirs = realloc(current_node->current_dir->subdirs, ((current_node->current_dir->number_of_sub_dirs + 1) * 3) * sizeof(Dir *));
		if (current_node->current_dir->subdirs == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
		/*}*/
	}
	/* Allocate memory for the new subdirectory */
	current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs] = malloc(sizeof(Dir *));
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

	/*printf("%s\n", current_node->current_dir->subdirs[current_node->current_dir->number_of_sub_dirs]->path);*/
	/* set parent */

	/* Increment the number of subdirectories */
	current_node->current_dir->number_of_sub_dirs++;
}
