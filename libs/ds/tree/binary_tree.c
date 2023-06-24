#include "include/binary_tree.h"


int main(){
    ZBinaryTree*      tree  =  NULL;
    ZBinaryTreeNode*  node  =  NULL;
    ZBinaryTreeNode*  right  =  NULL;

    tree = malloc( sizeof(ZBinaryTree) );
    node = malloc( sizeof(ZBinaryTreeNode) );

    tree->root = node;
    node->right = right;

    printf( "%p\n", &(tree->root->right) );

    return 0;
}
