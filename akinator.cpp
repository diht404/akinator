#include "akinator.h"

size_t treeGuessing(Tree *tree)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    char answer[BUFFER_SIZE] = "";
    printf("Please make a word.\n");

    Node *current_node = tree->root;
    while (current_node->left != nullptr
        and current_node->right != nullptr)
    {
        printf("%s?\n", current_node->value);
        printf("Please answer yes or no.\n");
        scanf("%s", answer);
        if (strcasecmp(answer, "yes") == 0)
        {
            current_node = current_node->left;
        }
        else if (strcasecmp(answer, "no") == 0)
        {
            current_node = current_node->right;
        }
        else
        {
            printf("I don't understand, try again.\n");
        }
    }
    printf("%s?\n", current_node->value);
    printf("Please answer yes or no.\n");
    scanf("%s", answer);

    if (strcasecmp(answer, "yes") == 0)
    {
        printf("I told you I would guess!\n");
    }
    else if (strcasecmp(answer, "no") == 0)
    {
        char correct_answer[BUFFER_SIZE] = "";
        skipUnusedSymbols();

        printf("What is the correct answer? \n");
        size_t correct_answer_size = gets(correct_answer) - 1;

        char delimiter_answer[BUFFER_SIZE] = "";
        printf("I don't understand "
               "that is the difference between \"%s\" and \"%s\"."
               "Can you please explain? \n",
               correct_answer,
               current_node->value);
        size_t delimiter_size = gets(delimiter_answer) - 1;

        insertNode(current_node,
                   correct_answer,
                   correct_answer_size,
                   delimiter_answer,
                   delimiter_size);
    }
    return TREE_NO_ERRORS;
}

size_t gets(char *s)
{
    assert(s != nullptr);

    size_t len = 0;
    char c = ' ';
    while (c != '\n' and c != EOF)
    {
        len++;
        c = getchar();
        if (c != EOF)
        {
            *s = c;
            s++;
        }
        if (c == EOF)
        {
            *s = '\0';
        }
    }
    return len;
}

int skipUnusedSymbols()
{
    int symbol = getchar();

    while (symbol != '\n')
    {
        if (symbol == EOF)
            return 0;
        symbol = getchar();
    }

    return 0;
}