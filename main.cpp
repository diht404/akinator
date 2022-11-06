#include "akinator.h"

int main()
{
    treeClearGraphLogFile();
    treeSetLogFile();

    enableVoiceOutput();

    Tree tree = {};
    treeCtor(&tree);
    readTree(&tree, AKINATOR_FILE);

    selectTask(&tree);

    treeDtor(&tree);

    treeCloseLogFile();
    return 0;
}