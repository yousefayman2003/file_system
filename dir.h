#ifndef DIR_H
#define DIR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*#include "file.h"*/

#define MAX_NAME_LENGTH 128
#define MAX_TYPE_LENGTH 64
#define MAX_PROTECTION_LENGTH 4
#define BLOCK_SIZE 32

typedef struct Dir Dir;
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

Current *initialize_current_node();
/**
 * create_dir - create new directory.
 * @name: name of file created.
 * Return: 1 if successfully created and 0 if else.
 */
void create_root();
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
#endif
