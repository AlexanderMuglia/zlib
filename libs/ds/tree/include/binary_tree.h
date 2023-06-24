#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../../../common/ZStatus.h"

/*
 * A node of a binary tree that stores a string as data
 */
typedef struct ZBinaryTreeNode
{
    struct          ZBinaryTreeNode*           left;
    struct          ZBinaryTreeNode*           right;
    char*                                      data;

} ZBinaryTreeNode;

/*
 * A binary tree type that holds a pointer to the root node
 */
typedef struct
{
    ZBinaryTreeNode*            root;

} ZBinaryTree;
