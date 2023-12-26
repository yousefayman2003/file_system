#ifndef DIR_H
#define DIR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_NAME_LENGTH 128
#define MAX_TYPE_LENGTH 64
#define MAX_PROTECTION_LENGTH 4
#define BLOCK_SIZE 32

#define MAX_COMMAND_LENGTH 50
#define MAX_ARGS_LENGTH 50
#define MAX_TOTAL_ARGS 10

typedef struct Dir Dir;

/*
 * struct file - Represents attributes of a file in a file system
 *
 * @name:       Name of the file (e.g., "project.docx")
 * @identifier: Unique number identifying the file within
 *               the file system (e.g., 91011)
 * @location:   Path indicating the logical location of the
 *               file (e.g., "C:\\Users\\YourUsername\\Documents")
 * @type:       Type of the file (e.g., "Document File")
 * @size:       Current size of the file in kilobytes (KB)
 * @blocks:     Number of blocks in which the file is stored
 * @protection: Access rights controlling read (r), write (w),
 *              and execute (x) permissions (e.g., "rw-")
 * @creationTime:      Timestamp indicating the file creation time
 * @modificationTime:  Timestamp indicating the last modification
 *                      time of the file's content
 * @accessTime: Timestamp indicating the last accessed or
 *              read time of the file
 * @content: String representing the content of the file
*/

typedef struct File {
    char name[MAX_NAME_LENGTH];
    int id;
    char *location;
    Dir *parent;
    char type[MAX_TYPE_LENGTH];
    double size;  /*in KB*/
    int blocks;
    char protection[MAX_PROTECTION_LENGTH];
    time_t creation_time;
    time_t modification_time;
    time_t access_time;
    char *content;
} File;

/**
 * Dir - is a struct representing Linux directory.
 * @name: Name of the directory.
 * @path: path to the file.
 * @files: Files represents in the directory.
 * @subdirs: Subdirs in the directory.
 */
typedef struct Dir
{
	char *name;
	struct Dir *parent;
	char *path;
	int size;
	char *dir_permissions;        /*"drwxrwxrwx"*/
	struct Dir **subdirs;
	File **files;
	int number_of_files;
	int number_of_sub_dirs;
	time_t creation_time;
	time_t last_modification_time;
} Dir;

typedef struct Current
{
	Dir *current_dir;
	File *current_file;
} Current;


extern Current *current_node;
extern Dir root;

Current *initialize_current_node();

void create_root(Dir *root);
Dir *create_dir(char *name);
void delete_dir(Dir *dir);
void list_dir_content();
void dir_info();
void change_dir_permissions(char *permession);
char *search_in_dir(char *searched_name);
void get_back();
void go_to_dir(char *name);
void go_to_file(File *file);
void appendSubdir(Dir *new_dir);
void appendFile(File *new_file);
File *create_file(char *filename);

/* file functions prototype */
File *create_file(char *filename);
char *read_file(int id);
int write_file(int id, char *content);
File *copy_file(int id);
void information_file(int id);
void change_perm_file(int id, char *perm);
void rename_file(int id, char *new_name);
void delete_file(int id);
void appendFile(File *new_file);
int get_id(char *file);
File *get_file(int id);
void get_chars_before_dot(char *input, char *result);
void get_chars_after_dot(char *input, char *result);

void help();
void parse_command(char *input, char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH], int *numArgs);
int handle_command(char *command, char args[MAX_TOTAL_ARGS][MAX_ARGS_LENGTH]);
#endif
