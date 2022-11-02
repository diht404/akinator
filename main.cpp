#include "akinator.h"

void nodeDump(Node *node, const char *text)
{
    fprintf(stderr,
            "%s %16p %16p %16p %s\n",
            text,
            node->left,
            node,
            node->right,
            node->value);
}

int main()
{
    Tree tree = {};
    treeCtor(&tree);
    readTree(&tree, "tree.txt");
    nodeDump(tree.root, "root");
    nodeDump(tree.root->left, "left root");
    nodeDump(tree.root->left->left, "left left");
    nodeDump(tree.root->left->right, "left right");
    nodeDump(tree.root->right, "right root");
    nodeDump(tree.root->right->left, "right left");
    nodeDump(tree.root->right->right, "right right");
    treeDump(&tree);
    return 0;
}