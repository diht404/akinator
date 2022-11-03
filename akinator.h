#ifndef AKINATOR__AKINATOR_H
#define AKINATOR__AKINATOR_H

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

#include "tree/tree.h"

const size_t BUFFER_SIZE = 128;

size_t treeGuessing(Tree *tree);

size_t gets(char *s);

int skipUnusedSymbols();

#endif //AKINATOR__AKINATOR_H
