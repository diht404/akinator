#include "akinator.h"

int main()
{
    Tree tree = {};
    treeCtor(&tree);
    readTree(&tree, AKINATOR_FILE);

    selectTask(&tree);

    treeDump(&tree);
    FILE *fp = fopen(AKINATOR_FILE, "w");
    treePrint(&tree, fp);
    fclose(fp);
    treeDtor(&tree);
    return 0;
}