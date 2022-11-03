#include "akinator.h"

int main()
{
    Tree tree = {};
    treeCtor(&tree);
    readTree(&tree, "tree.txt");
    treeDump(&tree);
    return 0;
}