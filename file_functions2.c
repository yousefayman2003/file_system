#include "file.h"

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
