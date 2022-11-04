#ifndef AKINATOR_TREE_LOGS_H
#define AKINATOR_TREE_LOGS_H

#include "tree.h"

void treeSetLogFile();

void treeClearGraphLogFile();

void treeCloseLogFile();

size_t treeDump(Tree *tree);

size_t createGraph(Tree *tree, const char *photo_name);

size_t createGraphNodes(Node *node, FILE *fp);

size_t createGraphEdges(Node *node, FILE *fp);

#endif //AKINATOR_TREE_LOGS_H
