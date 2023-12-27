/*#include "file.h"*/
#include "dir.h"
/* Counter for file identifiers */
static int file_count = 0;

/**
 * create_file - Creates a new file with specified attributes.
 * @filename: Name of the file.
 * @filepath: Path where the file will be located.
 * Return: Pointer to the newly created File, NULL if error occured.
*/
File *create_file(char *filename)
{
	File *file = malloc(sizeof(File));
	time_t current_time;
	
	if (!filename)
	{
		perror("Error missing args");
		return (NULL);
	}
	
	if (!file)
	{
		perror("Error creating the file");
		return (NULL);
	}
	
	/* initalize values */
	file->size = 0;
	file->blocks = 0;
	strcpy(file->protection, "644");
	file->content = malloc(128);
	if (!(file->content))
	{
		perror("Error creating the file");
		return (NULL);
	}
	file->content = "\0";
	
	/* Get current time */
	time(&current_time);
	file->creation_time = current_time;
	file->modification_time = current_time;
	file->access_time = current_time;
	
	file->id = file_count++;
	/*file->location = malloc(strlen(filepath) + 1);
	if (!(file->location))
        {
                perror("Error creating the file");
                return (NULL);
        } */
	/*strcpy(file->location, "None");*/

	/* Splitting filename into name and type */
        char *dot = strrchr(filename, '.');
        if (dot != NULL)
        {
                /* set name of file */
                strncpy(file->name, filename, dot - filename);
                file->name[dot - filename] = '\0';

                /* set type of file */
                strncpy(file->type, dot + 1, sizeof(file->type) - 1);
                file->type[sizeof(file->type) - 1] = '\0';
        }
        else
        {
                /* set name of file */
                strncpy(file->name, filename, sizeof(file->name) - 1);
                file->name[sizeof(file->name) - 1] = '\0';

                /* set type to an empty string */
                strcpy(file->type, "");
        }
	appendFile(file);
	return (file);
}

/**
 * read_file - reads the content of a file
 * @id: file id
 * Return: content of file
*/
char *read_file(int id)
{
	File *file;

	if (id != -1)
	{
		file = get_file(id);
		time(&file->access_time);
		return (file->content);
	}
	return (NULL);
}

/**
 * write_file - write content to a file
 * @id: file id
 * @content: content to write
 * Return: 0 on success, -1 on fail
*/
int write_file(int id, char *content)
{
	File *file;

	if (id == -1)
	{
		printf("File not found.\n");
		return (-1);
	}
	if (!content)
	{
		printf("Missing content to write.");
		return (-1);
	}
	
	file = get_file(id);
	/* Free exising content (if any) */
	if (file->content)
	{
		file->content = NULL;
	}

	/* Allocate memory for new content */
	file->content = malloc(sizeof(content) + 1);
	
	if (!(file->content))
	{
		perror("Couldn't write file");
		return (-1);
	}
	strcpy(file->content, content);

	/* Calculate size */
	file->size = (sizeof(content) / 1000);
	
	/* Calculate blocks */
	file->blocks = (sizeof(content) / BLOCK_SIZE) + 1;
	
	/* Update modification_time */
	time(&file->modification_time);

	return (0);
}

/**
 * copy_file - copies a file
 * @id: file id
 * @parent: parent directory.
*/
void *copy_file(int id, char *parent)
{
	File *file, *copy;
	if (id == -1)
	{
		printf("Error: File not found.\n");
		return;
	}
	file = get_file(id);
	copy = malloc(sizeof(File));
	
	if (file == NULL)
		return NULL;

	if (!copy)
	{
		perror("Error couldn't copy file");
		return (NULL);
	}

	/* Copy the attributes of the original file to the new file */
	copy->id = file->id;
	copy->size = file->size;
	copy->blocks = file->blocks;
	copy->creation_time = file->creation_time;
	copy->modification_time = file->modification_time;
	copy->access_time = file->access_time;

	/* Allocate memory for string attributes and copy content */
	strcpy(copy->name, file->name);
	strcpy(copy->type, file->type);

	/* Allocate memory for content and location strings */
	copy->content = malloc(strlen(file->content) + 1);
	copy->location = malloc(strlen(file->location) + 1);

	if (copy->content == NULL || copy->location == NULL)
	{
		perror("Error: Memory allocation failed for content or location");
		free(copy);
		return (NULL);
	}
	strcpy(copy->content, file->content);
	strcpy(copy->location, file->location);
	strcpy(copy->protection, file->protection);
	
	return (copy);
}

/**
 * information_file - retrieves all information about a file
 * @id: file id
*/
void information_file(int id)
{
	File *file = get_file(id);

	if (file == NULL)
	{
		printf("File is not found.\n");
		return;
	}

	printf("File Information:\n");
	printf("Name: %s\n", file->name);
	printf("Id: %d\n", file->id);
	//printf("Location: %s\n", file->location);
	printf("Type: %s\n", file->type);
	printf("Size: %.2f KB\n", file->size);
	printf("Blocks: %d\n", file->blocks);
	printf("Protection: %s\n", file->protection);

	/* Convert timestamps to human-readable format */
	char creation_time[50];
	char modification_time[50];
	char access_time[50];

	strftime(creation_time, sizeof(creation_time), "%Y-%m-%d %H:%M:%S", localtime(&(file->creation_time)));
	strftime(modification_time, sizeof(modification_time), "%Y-%m-%d %H:%M:%S", localtime(&(file->modification_time)));
	strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", localtime(&(file->access_time)));

	printf("Creation Time: %s\n", creation_time);
	printf("Modification Time: %s\n", modification_time);
	printf("Access Time: %s\n", access_time);
	printf("Content: %s\n", file->content);
}
