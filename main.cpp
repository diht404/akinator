#include "akinator.h"

int main()
{
    Tree tree = {};
    const char *tree_filename = "tree.txt";
    treeCtor(&tree);
    readTree(&tree, tree_filename);
    treeDump(&tree);
    FILE *fp = fopen(tree_filename, "w");
    treePrint(&tree, fp);
    fclose(fp);
    treeDtor(&tree);
    return 0;
}