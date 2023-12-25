#ifndef DIR_H
#define DIR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

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
	int size;
	char *dir_permissions;        /*"drwxrwxrwx"*/
	struct Dir *first_dir;
	struct Dir *next_sibling;
	File *first_file;
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

Current* initialize_current_node();
/**
 * create_dir - create new directory.
 * @name: name of file created.
 * Return: 1 if successfully created and 0 if else.
 */
void create_root();
void create_dir(Dir **dir, char *name);
void delete_dir(Dir *dir);
void list_dir_content();
void dir_info();
void change_dir_permissions(char *permession);
char *search_in_dir(char *searched_name);
void get_back();
void go_to_dir(Dir *dir);
void go_to_file(File *file);
void appendFile(Dir *dir, char *fileName);
void appendSubdir(Dir **new_dir);
#endif
