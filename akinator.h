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

/**
 * @brief enables voice output
 */
void enableVoiceOutput();

/**
 * @brief disables voice output
 */
void disableVoiceOutput();

/**
 * @brief suggests to the user to select a task and runs it
 *
 * @param tree tree to run task on
 * @return error code
 */
size_t selectTask(Tree *tree);

/**
 * @brief guesses word, using tree
 *
 * @param tree tree to run guessing on
 * @return error code
 */
size_t treeGuessing(Tree *tree);

/**
 * @brief compares to words using tree
 *
 * @param tree tree to use in comparison
 * @param first_entity first entity to compare
 * @param second_entity second entity to compare
 * @return error code
 */
size_t getComparison(Tree *tree, Val_t first_entity, Val_t second_entity);

/**
 * @brief outputs definition of value using tree
 *
 * @param tree tree to use in definition
 * @param value value to get definition
 * @return error code
 */
size_t getDefinition(Tree *tree, Val_t value);

/**
 * @brief pushes elements of tree to stack until first occurrence of
 *
 * @param tree tree with elements
 * @param stack stack for pushing
 * @param value value to search
 * @return node with value
 */
Node *pushUntilValue(Tree *tree, Stack *stack, Val_t value);

/**
 * @brief creates definition of definition_node using stack
 *
 * @param stack stack with elements that will be used in definition
 * @param definition_node node to get definition of
 * @param definition struct with definition and its length
 * @return error code
 */
size_t createDefinition(Stack *stack,
                        Node *definition_node,
                        Definition *definition);

/**
 * @brief pushes subtree of node to stack until value or
 * all elements if value not exist
 *
 * @param node root of tree to push
 * @param stack stack to push pointers of nodes
 * @param value value to search
 * @return
 */
size_t pushPointersToStack(Node *node, Stack *stack, Val_t value);

/**
 * @brief outputs text as stdout and with voice it is enabled
 *
 * @param text text to print
 * @param ... args of format string
 */
void outputText(const char *text, ...);

#endif //AKINATOR__AKINATOR_H
