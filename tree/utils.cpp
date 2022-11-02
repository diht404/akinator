#include "utils.h"

long getLenOfFile(FILE *fp)
{
    struct stat buff = {};
    fstat(fileno(fp), &buff);
    long lenOfFile = buff.st_size;
    return lenOfFile;
}

char *readFileToBuf(FILE *fp, long *lenOfFile)
{
    assert(fp != nullptr);
    assert(lenOfFile != nullptr);

    *lenOfFile = getLenOfFile(fp);

    char *txt = (char *) calloc(*lenOfFile + 1, sizeof(char));
    if (txt == nullptr)
    {
        fprintf(stderr, "Can't allocate memory.");
    }
    fread(txt, sizeof(char), *lenOfFile, fp);
    return txt;
}