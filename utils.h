#ifndef AKINATOR__UTILS_H
#define AKINATOR__UTILS_H

#include "stdio.h"
#include "sys/stat.h"
#include "assert.h"
#include "stdlib.h"

long getLenOfFile(FILE *fp);

char *readFileToBuf(FILE *fp, long *lenOfFile);

size_t gets(char *s);

int skipUnusedSymbols();

#endif //AKINATOR__UTILS_H
