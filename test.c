#include "file.h"


int main()
{
	File *myFile = create_file("example.txt");
	TreeNode *fileNode = createFileNode(myFile);
}
