#include "file.h"

// Function to create a new tree node for a file
TreeNode *createFileNode(File *file) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->isFile = 1;
        newNode->data.filePtr = file;
        newNode->childCount = 0;
    }
    return newNode;
}

// Function to create a new tree node for a directory
TreeNode *createDirNode(Dir *dir) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->isFile = 0;
        newNode->data.dirPtr = dir;
        newNode->childCount = 0;
    }
    return newNode;
}

// Function to add a child node to a parent node in the tree
void addChild(TreeNode *parent, TreeNode *child) {
    if (parent != NULL && child != NULL && parent->childCount < MAX_CHILDREN) {
        parent->children[parent->childCount++] = child;
    }
}
