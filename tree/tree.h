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
    NODE_IS_NULLPTR          = 2,
    TREE_FILENAME_IS_NULLPTR = 3,
    CANT_OPEN_TREE_FILE      = 4,
    TREE_CANT_ALLOCATE_MEMORY= 5,
    TREE_NO_SUCH_ELEMENT     = 6,
    TOO_MANY_ATTEMPTS_TO_READ= 7,
};

size_t treeCtor(Tree *tree);

size_t nodeCtor(Node *node);

size_t treeDtor(Tree *tree);

size_t nodeDtor(Node *node);

size_t treeDump(Tree *tree);

size_t createGraph(Tree *tree, const char *photo_name);

size_t createGraphNodes(Node *node, FILE *fp);

size_t createGraphEdges(Node *node, FILE *fp);

size_t treePrint(Tree *tree, FILE *fp);

size_t nodePreOrderPrint(Node *node, FILE *fp, size_t num_spaces = 0);

size_t nodeInOrderPrint(Node *node);

size_t nodePostOrderPrint(Node *node);

size_t readTree(Tree *tree, const char *filename);

size_t addNode(Tree *tree, Node *node, char **buffer, char **readPtr, long lenOfFile);

size_t insertNode(Node *node,
                  char *value,
                  size_t value_size,
                  char *delimiter,
                  size_t delimiter_size);

#define CHECK_NULLPTR_ERROR(value, error) \
    {                                     \
        assert(#value && (int)error);     \
        if (value == nullptr)             \
            return error;                 \
    }

#endif //AKINATOR__TREE_H
