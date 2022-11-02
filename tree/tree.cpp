#include "tree.h"

size_t treeCtor(Tree *tree)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    tree->root = nullptr;
    tree->size = 0;
    return TREE_NO_ERRORS;
}

size_t treeDtor(Tree *tree)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    // TODO: tree dtor
    return TREE_NO_ERRORS;
}

size_t treeDump(Tree *tree)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    char filename[128] = "logs.html";
    char photo_name[128] = "log.jpg";

    FILE *fp = fopen(filename, "w");

    fprintf(fp, "<pre>\n");

    createGraph(tree, photo_name);
    fprintf(fp, "<img src=%s />\n", photo_name);

    fclose(fp);
}

size_t createGraph(Tree *tree, const char *photo_name)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)
    CHECK_NULLPTR_ERROR(photo_name, TREE_FILENAME_IS_NULLPTR)

    FILE *fp = fopen(GRAPH_FILENAME, "w");
    fprintf(fp, "digraph TREE {\n"
                "    rankdir=LR;\n");

    createGraphNodes(tree->root, fp);
    createGraphEdges(tree->root, fp);

    // close graph with }
    fprintf(fp, "}\n");

    char command[128] = "";
    fclose(fp);
    sprintf(command, "dot %s -T jpg -o %s", GRAPH_FILENAME, photo_name);
    system(command);
    return TREE_NO_ERRORS;
}

size_t createGraphNodes(Node *node, FILE *fp)
{
    if (!node)
        return TREE_NO_ERRORS;

    size_t error = TREE_NO_ERRORS;

    fprintf(fp,
            "    node_%p[shape=\"record\", \n"
            "        fillcolor=%s, \n"
            "        style=\"rounded, filled\", \n"
            "        label=\"\n"
            "            VALUE = %s |\n"
            "            {{LEFT | %p} | {INDEX | %p} | {RIGHT | %p}}\"]\n",
            node,
            GREEN_COLOR,
            node->value,
            node->left,
            node,
            node->right);

    if (node->left)
        error = createGraphNodes(node->left, fp);
    if (error)
        return error;

    if (node->right)
        error = createGraphNodes(node->right, fp);
    if (error)
        return error;

    return TREE_NO_ERRORS;
}

size_t createGraphEdges(Node *node, FILE *fp)
{
    if (!node)
        return TREE_NO_ERRORS;

    size_t error = TREE_NO_ERRORS;

    if (node->left)
    {
        fprintf(fp,
                "    node_%p->node_%p;",
                node,
                node->left);
        error = createGraphEdges(node->left, fp);
        if (error)
            return error;
    }

    if (node->right)
    {
        fprintf(fp,
                "    node_%p->node_%p;",
                node,
                node->right);
        error = createGraphEdges(node->right, fp);
        if (error)
            return error;
    }

    return TREE_NO_ERRORS;
}

size_t nodePreOrderPrint(Node *node)
{
    if (!node)
        return TREE_NO_ERRORS;

    size_t error = TREE_NO_ERRORS;

    printf("%s\n", node->value);

    if (node->left)
        error = nodePreOrderPrint(node->left);
    if (error)
        return error;

    if (node->right)
        error = nodePreOrderPrint(node->right);
    if (error)
        return error;

    return TREE_NO_ERRORS;
}

size_t nodeInOrderPrint(Node *node)
{
    if (!node)
        return TREE_NO_ERRORS;

    size_t error = TREE_NO_ERRORS;

    if (node->left)
        error = nodeInOrderPrint(node->left);
    if (error)
        return error;

    printf("%s\n", node->value);

    if (node->right)
        error = nodeInOrderPrint(node->right);
    if (error)
        return error;

    return TREE_NO_ERRORS;
}

size_t nodePostOrderPrint(Node *node)
{
    if (!node)
        return TREE_NO_ERRORS;

    size_t error = TREE_NO_ERRORS;

    if (node->left)
        error = nodePostOrderPrint(node->left);
    if (error)
        return error;

    if (node->right)
        error = nodePostOrderPrint(node->right);
    if (error)
        return error;

    printf("%s\n", node->value);

    return TREE_NO_ERRORS;
}

size_t readTree(Tree *tree, const char *filename)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    FILE *fp = fopen(filename, "r");
    if (fp == nullptr)
        return CANT_OPEN_TREE_FILE;

    long lenOfFile = 0;
    char *tree_buffer = readFileToBuf(fp, &lenOfFile);
    fclose(fp);


    Node *new_node = (Node *) calloc(1, sizeof(tree->root[0]));
    if (new_node == nullptr)
        return CANT_ALLOCATE_MEMORY;
    tree->root = new_node;

    char *readPtr = tree_buffer;

    addNode(tree, tree->root, &tree_buffer, &readPtr, lenOfFile);

    return TREE_NO_ERRORS;
}

void addNode(Tree *tree, Node *node, char **buffer, char **readPtr, long lenOfFile)
{
    bool isToken = false;
    char *startTokenPtr = nullptr;
    char *endTokenPtr = nullptr;
    while (*readPtr < *buffer + lenOfFile)
    {
        if (**readPtr == '}')
        {
            if (isToken > 0)
            {
                Node *new_node = nullptr;
                if (node == tree->root and tree->root->value == nullptr)
                    new_node = tree->root;
                else
                    new_node = (Node *) calloc(1, sizeof(Node));

                new_node->left = nullptr;
                new_node->right = nullptr;

                if (tree->root->value != nullptr)
                {
                    if (node->left == nullptr)
                        node->left = new_node;
                    else if (node->right == nullptr)
                        node->right = new_node;
                    else
                        fprintf(stderr, "Both is not NULLPTR\n");
                }

                if (*startTokenPtr == '\"')
                    startTokenPtr++;
                if (*endTokenPtr == '\"')
                    endTokenPtr--;

                new_node->value =
                    (char *) calloc(endTokenPtr - startTokenPtr + 1,
                                    sizeof(new_node->value[0]));

                fprintf(stderr,
                        "WRITE NUM %ld TOKENS: ---%s---\n"
                        "NODE: %p\n",
                        endTokenPtr - startTokenPtr + 1,
                        startTokenPtr, node);

                memcpy(new_node->value,
                       startTokenPtr,
                       endTokenPtr - startTokenPtr + 1);

                isToken = false;
                if (node->right != nullptr)
                    break;
//                (*readPtr)++;
//                fprintf(stderr,
//                        "BUFFER_STATE: \n%s_\n tree.root=%p \nnode=%p\n",
//                        *readPtr,
//                        tree->root,
//                        node);
//                addNode(tree, new_node, buffer, readPtr, lenOfFile);
            }
            (*readPtr)++;
        }
        else if (**readPtr == '{')
        {
            if (isToken > 0)
            {
                Node *new_node = nullptr;
                if (node == tree->root and tree->root->value == nullptr)
                    new_node = tree->root;
                else
                    new_node = (Node *) calloc(1, sizeof(Node));
                isToken = false;

                if (tree->root->value != nullptr)
                {
                    if (node->left == nullptr)
                        node->left = new_node;
                    else if (node->right == nullptr)
                        node->right = new_node;
                    else
                        fprintf(stderr, "Both is not NULLPTR\n");
                }

                if (*startTokenPtr == '\"')
                    startTokenPtr++;
                if (*endTokenPtr == '\"')
                    endTokenPtr--;

                new_node->value =
                    (char *) calloc(endTokenPtr - startTokenPtr + 1,
                                    sizeof(new_node->value[0]));
                memcpy(new_node->value,
                       startTokenPtr,
                       endTokenPtr - startTokenPtr + 1);

                addNode(tree, new_node, buffer, readPtr, lenOfFile);
            }
            (*readPtr)++;
        }
        else
        {
            if (!isToken and **readPtr != ' ' and **readPtr != '\n')
            {
                startTokenPtr = *readPtr;
                isToken = true;
            }
            if (**readPtr != ' ' and **readPtr != '\n')
                endTokenPtr = *readPtr;
            (*readPtr)++;
        }
    }
}
