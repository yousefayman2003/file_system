#include "dir.h"

// Function to test creating a file
void test_create_file() {
    File *newFile = create_file("test.txt", "/path/to/documents");

    // Assertion checks if the file creation was successful
    assert(newFile != NULL);
    
    // Additional assertions to check file attributes, modify as needed
    assert(strcmp(newFile->name, "test") == 0);
    assert(strcmp(newFile->type, "txt") == 0);
    assert(strcmp(newFile->location, "/path/to/documents") == 0);
    
    // Clean up memory
    free(newFile);
}

// Function to test writing and reading from a file
void test_write_read_file() {
    File *newFile = create_file("test.txt", "/path/to/documents");
    assert(newFile != NULL);
    
    // Write content to the file
    char content[] = "This is a test content.";
    time_t previous_mod = newFile->modification_time;
    sleep(1);
    write_file(newFile, content);
    assert(strcmp(newFile->content, "This is a test content.") == 0);
    assert(previous_mod != newFile->modification_time);
    
    // Read content from the file
    time_t prev_access = newFile->access_time;
    sleep(1);
    char *readContent = read_file(newFile);
    assert(readContent != NULL);
    assert(prev_access != newFile->access_time);

    // Check if content was read successfully
    assert(strcmp(readContent, content) == 0);

    // Clean up memory
    free(readContent);
    free(newFile);
}

// Function to test the copy_file function
void test_copy_file() {
    // Create an original file with some attributes
    File originalFile = {
        .id = 123,
        .size = 1024.5,
        .blocks = 5,
        .creation_time = time(NULL),
        .modification_time = time(NULL),
        .access_time = time(NULL),
        .name = "original_file.txt",
        .type = "text",
        .content = "This is the content of the original file.",
        .protection = "rw-",
        .location = "/path/to/original_file"
    };

    // Copy the original file
    File *copiedFile = copy_file(&originalFile);

    // Check if the copy was successful
    assert(copiedFile != NULL);
    assert(originalFile.id == copiedFile->id);
    assert(originalFile.size == copiedFile->size);
    assert(originalFile.blocks == copiedFile->blocks);
    assert(originalFile.creation_time == copiedFile->creation_time);
    assert(originalFile.modification_time == copiedFile->modification_time);
    assert(originalFile.access_time == copiedFile->access_time);
    assert(strcmp(originalFile.name, copiedFile->name) == 0);
    assert(strcmp(originalFile.type, copiedFile->type) == 0);
    assert(strcmp(originalFile.content, copiedFile->content) == 0);
    assert(strcmp(originalFile.protection, copiedFile->protection) == 0);
    assert(strcmp(originalFile.location, copiedFile->location) == 0);


    // Free memory for the copied file
    free(copiedFile);
}

// Function to test the information_file function
void test_information_file() {
    // Create a sample file
    File *testFile = malloc(sizeof(File));
    if (testFile == NULL) {
        perror("Memory allocation failed");
        return;
    }

    // Initialize sample attributes (adjust according to your File structure)
    testFile->id = 12345;
    testFile->size = 1024.56;
    testFile->blocks = 8;
    testFile->creation_time = time(NULL);
    testFile->modification_time = time(NULL) - 1000;
    testFile->access_time = time(NULL) - 500;
    strcpy(testFile->name, "sample.txt");
    strcpy(testFile->type, "Text File");
    strcpy(testFile->location, "/path/to/file");
    strcpy(testFile->protection, "rw-");
    testFile->content = "Sample content for testing.";

    // Call the function to display file information
    information_file(testFile);

    // Clean up memory
    free(testFile);
}

// Function to test the change_perm_file function
void test_change_perm_file() {
    // Create a sample file
    File *testFile = malloc(sizeof(File));
    if (testFile == NULL) {
        perror("Memory allocation failed");
        return;
    }

    // Initialize sample attributes
    strcpy(testFile->name, "sample.txt");
    strcpy(testFile->type, "Text File");
    strcpy(testFile->location, "/path/to/file");
    strcpy(testFile->protection, "rw-");
	
    char *prev_perm = malloc(sizeof(testFile->protection) + 1);
    strcpy(prev_perm, testFile->protection);
    // Change file permission
    change_perm_file(testFile, "r--");

    // assert they are not equal
    assert(strcmp(prev_perm, testFile->protection) != 0);
    // Clean up memory
    free(testFile);
    free(prev_perm);
}

// Test function for rename_file
void test_rename_file() {
    File test_file;
    strcpy(test_file.name, "example");
    strcpy(test_file.type, "txt");

    // Perform the rename operation
    char new_name[] = "new_example.docx";
    rename_file(&test_file, new_name);

    // Verify the result after renaming
    assert(strcmp(test_file.name, "new_example") == 0);
    assert(strcmp(test_file.type, "docx") == 0);

}

int main() {
    test_create_file();
    test_write_read_file();
    test_copy_file();
    test_information_file();
    test_change_perm_file();
    test_rename_file();

    printf("All tests passed!\n");
    return (0);
}
