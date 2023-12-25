#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

/* MACROS */
#define MAX_NAME_LENGTH 128
#define MAX_TYPE_LENGTH 64
#define MAX_PROTECTION_LENGTH 4
#define BLOCK_SIZE 32

/*
 * struct file - Represents attributes of a file in a file system
 *
 * @name:       Name of the file (e.g., "project.docx")
 * @identifier: Unique number identifying the file within
 * 		 the file system (e.g., 91011)
 * @location:   Path indicating the logical location of the
 * 		 file (e.g., "C:\\Users\\YourUsername\\Documents")
 * @type:       Type of the file (e.g., "Document File")
 * @size:       Current size of the file in kilobytes (KB)
 * @blocks:     Number of blocks in which the file is stored
 * @protection: Access rights controlling read (r), write (w),
 * 		and execute (x) permissions (e.g., "rw-")
 * @creationTime:      Timestamp indicating the file creation time
 * @modificationTime:  Timestamp indicating the last modification
 * 			time of the file's content
 * @accessTime: Timestamp indicating the last accessed or
 * 		read time of the file
 * @content: String representing the content of the file
*/
typedef struct File {
    char name[MAX_NAME_LENGTH];
    int id;
    char *location;
    char type[MAX_TYPE_LENGTH];
    double size; /* in KB */
    int blocks;
    char protection[MAX_PROTECTION_LENGTH];
    time_t creation_time;
    time_t modification_time;
    time_t access_time;
    char *content;
} File;

/* function prototype */
File *create_file(char *filename);
char *read_file(File *file);
int write_file(File *file, char *content);
File *copy_file(File *file);
void information_file(File *file);
void change_perm_file(File *file, char *perm);
void rename_file(File *file, char *new_name);

#endif /* FILE_H */
