#ifndef AKINATOR__TREE_H
#define AKINATOR__TREE_H

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "config.h"
#include "utils.h"
#include "cstring"

struct Node
{
    Val_t value = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

struct Tree
{
    Node *root = nullptr;
    size_t size = 0;
};

enum TreeErrors
{
    TREE_NO_ERRORS           = 0,
    TREE_IS_NULLPTR          = 1,
    TREE_FILENAME_IS_NULLPTR = 2,
    CANT_OPEN_TREE_FILE      = 3,
    CANT_ALLOCATE_MEMORY     = 4,
};

size_t treeCtor(Tree *tree);

size_t treeDtor(Tree *tree);

size_t treeDump(Tree *tree);

size_t createGraph(Tree *tree, const char *photo_name);

size_t createGraphNodes(Node *node, FILE *fp);

size_t createGraphEdges(Node *node, FILE *fp);

size_t nodePreOrderPrint(Node *node);

size_t nodeInOrderPrint(Node *node);

size_t nodePostOrderPrint(Node *node);

size_t readTree(Tree *tree, const char *filename);

void addNode(Tree *tree, Node *node, char **buffer, char **readPtr, long lenOfFile);

#define CHECK_NULLPTR_ERROR(value, error) \
    {                                     \
        assert(#value && (int)error);     \
        if (value == nullptr)             \
            return error;                 \
    }

#endif //AKINATOR__TREE_H
