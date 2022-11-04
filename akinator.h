#ifndef AKINATOR__AKINATOR_H
#define AKINATOR__AKINATOR_H

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "tree/tree.h"
#include "tree/logs.h"
#include "stack/stack.h"

const size_t BUFFER_SIZE = 128;
const char AKINATOR_FILE[] = "tree.txt";

size_t selectTask(Tree *tree);

size_t treeGuessing(Tree *tree);

size_t getDefinition(Tree *tree, Val_t value);

size_t pushPointersToStack(Node *node, Stack *stack, Val_t value);

#endif //AKINATOR__AKINATOR_H
