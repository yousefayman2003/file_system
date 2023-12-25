#include "dir.h"
Current *current_node;

int main()
{
        Dir *root, *new_dir;
        current_node = initialize_current_node();
        create_root(&root);
	dir_info();
	create_dir(&new_dir, "first file");
	dir_info();
/**    test_create_file();
    test_write_read_file();
    test_copy_file();
    test_information_file();
    test_change_perm_file();
    test_rename_file();*/
	delete_dir(new_dir);
	free(current_node);
    printf("All tests passed!\n");
    return (0);
}
