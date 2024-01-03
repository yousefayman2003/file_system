# Linux File System Project

## Project Overview

This project involves the implementation of a basic file system using data structures. The file system follows a hierarchical structure similar to many file systems used in operating systems. It supports directories, files, and various file-related operations. The implementation is geared towards a simplified representation of a file system found in Linux.

## Description

Most file systems today organize files in a tree structure, with a root node at the top and subdirectories and files underneath. The file system is responsible for organizing, storing, securing, searching, and manipulating files. This project focuses on implementing a simplified file system with the following features:

### File System Structure

- **Root Node:** The top-level node representing the root directory.
- **Directories:** Organized in a tree structure, each directory can contain files and subdirectories.
- **Files:** Contain attributes such as name, size, permissions, and timestamps.

### Types of Files

1. **File Attributes:**
   - Name
   - Identifier
   - Location
   - Type
   - Size
   - Blocks
   - Protection
   - Creation Time
   - Modification Time
   - Access Time
   - Content

2. **File Actions and Functions:**
   - Create File
   - Read from File
   - Write to File
   - Copy a File
   - Move/Rename a File
   - Delete a File
   - Get File Information
   - Change File Permissions

3. **Directory Attributes:**
   - Type
   - Content (may have children: files and subdirectories)

4. **Directory Actions and Functions:**
   - Create a Directory (Folder)
   - Delete a Directory
   - List Directory Contents
   - Get Directory Information
   - Change Directory Permissions
   - Search in Directory (retrieve files and subdirectories with a similar name)

5. **Root Node (Partition) Attributes:**
   - Partition Label/Name
   - UUID (Universally Unique Identifier)
   - Size
   - Used Space
   - Free Space
   - Block Size

## Usage

To use this file system, functions such as creating directories, creating files, listing directory contents, and more are provided. The project aims to showcase the fundamental operations of a file system in a simplified manner.

## Implementation Details

The file system is implemented using a combination of data structures, including structs for `Dir` (directory) and `Current` (current state of the file system). Operations on the file system, such as moving between directories, creating files, and changing permissions, are implemented through the provided functions.

## File and Directory Actions

- **Creating a Root Directory:** `create_root`
- **Moving Back to Parent Directory:** `get_back`
- **Moving to Root Directory:** `get_to_root`
- **Moving to a Specific Directory:** `go_to_dir`
- **Moving to a Specific File:** `go_to_file`
- **Initializing the Current Node:** `initialize_current_node`
- **Appending a Subdirectory:** `appendSubdir`

## Future Enhancements

This project serves as a foundation for further development and can be extended to include additional file system features and improvements. Future enhancements might include more sophisticated file and directory management, support for different file types, and improved user interaction.

Feel free to explore and expand upon this project according to your needs and requirements!
