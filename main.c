#include "dir.h"
Current *current_node;

int main()
{
        Dir root, *new_dir1, *new_dir2;
        current_node = initialize_current_node();
        create_root(root);
	dir_info();
	new_dir1 = create_dir("first file");
	new_dir1 = create_dir("first file");
	dir_info();
	change_dir_permissions("dr-x---rxw");
	dir_info();
	list_dir_content();
	search_in_dir("first file");
	go_to_dir("first file");
	list_dir_content();
	dir_info();
	get_back();
	dir_info();
/**    test_create_file();
    test_write_read_file();
    test_copy_file();
    test_information_file();
    test_change_perm_file();
    test_rename_file();*/
	/*delete_dir(new_dir);*/
	free(current_node);
    printf("All tests passed!\n");
    return (0);
}
