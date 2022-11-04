#ifndef AKINATOR__AKINATOR_H
#define AKINATOR__AKINATOR_H

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "tree/tree.h"
#include "tree/logs.h"
#include "stack/stack.h"

const size_t BUFFER_SIZE = 1024;
const char AKINATOR_FILE[] = "tree.txt";

struct Definition
{
    char definition[BUFFER_SIZE][BUFFER_SIZE] = {};
    int length = 0;
};

void setVoiceOutput();

void disableVoiceOutput();

size_t selectTask(Tree *tree);

size_t treeGuessing(Tree *tree);

size_t getComparison(Tree *tree, Val_t first_entity, Val_t second_entity);

size_t getDefinition(Tree *tree, Val_t value);

Node *pushUntilValue(Tree *tree, Stack *stack, Val_t value);

size_t createDefinition(Stack *stack,
                        Node *definition_node,
                        Definition *definition);

size_t pushPointersToStack(Node *node, Stack *stack, Val_t value);

void outputText(const char *formatString, ...);

#endif //AKINATOR__AKINATOR_H
