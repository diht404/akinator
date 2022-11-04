#include "akinator.h"

size_t selectTask(Tree *tree)
{
    while (true)
    {
        int task = 0;
        printf("Please, select a task:\n"
               "0 - exit\n"
               "1 - guessing\n"
               "2 - definition\n"
               "3 - comparison\n"
               "4 - dump\n"
               "5 - save changes\n"
               "6 - set to audio.\n");

        int correct = scanf("%d", &task);
        int readCount = 1;

        while (correct != 1 && readCount < 5)
        {
            printf("Incorrect number, try again!\n");
            skipUnusedSymbols();
            readCount += 1;
            correct = scanf("%d", &task);
        }

        if (readCount == 5)
            break;

        switch (task)
        {
            case 0:
            {
                printf("Good bye!\n");
                return TREE_NO_ERRORS;
            }
            case 1:
            {
                treeGuessing(tree);
                break;
            }
            case 2:
            {
                char buffer[BUFFER_SIZE] = "";
                printf("Definition of what you want?\n");
                skipUnusedSymbols();
                size_t len = gets(buffer);
                buffer[len - 1] = '\0';
                getDefinition(tree, buffer);
                break;
            }
            case 3:
            {
                printf("Comparison of what you want?\n");

                char first_entity[BUFFER_SIZE] = "";
                printf("Enter first entity: \n");
                skipUnusedSymbols();
                size_t first_len = gets(first_entity);
                first_entity[first_len - 1] = '\0';

                char second_entity[BUFFER_SIZE] = "";
                printf("Enter first entity: \n");
                size_t second_len = gets(second_entity);
                second_entity[second_len - 1] = '\0';

                getComparison(tree, first_entity, second_entity);
                break;
            }
            case 4:
            {
                printf("Tree dumped.\n");
                treeDump(tree);
                break;
            }
            case 5:
            {
                FILE *fp = fopen(AKINATOR_FILE, "w");
                treePrint(tree, fp);
                fclose(fp);
                break;
            }
            case 6:
            {
                // todo: speech
                break;
            }
            default:
            {
                printf("Unknown command code: %d\n", task);
                break;
            }
        }
    }
}

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
        size_t correct_answer_size = gets(correct_answer);
        correct_answer[correct_answer_size - 1] = '\0';

        char delimiter_answer[BUFFER_SIZE] = "";
        printf("I don't understand "
               "that is the difference between \"%s\" and \"%s\". "
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

size_t getComparison(Tree *tree,
                     Val_t first_entity,
                     Val_t second_entity)
{
    if (strcasecmp(first_entity, second_entity) == 0)
    {
        printf("It's the same. What you want yo compare?..\n");
        return TREE_NO_ERRORS;
    }

    Stack stack = {};
    size_t error = STACK_NO_ERRORS;
    stackCtor(&stack, 0, &error)

    Node *definition_node = pushUntilValue(tree, &stack, first_entity);
    if (definition_node == nullptr)
    {
        printf("I don't know what is %s.\n", first_entity);
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        printf("%s is %s\n", first_entity, first_entity);
        return TREE_NO_ERRORS;
    }

    Definition definition_first = {};
    createDefinition(&stack, definition_node, &definition_first);

    definition_node = pushUntilValue(tree, &stack, second_entity);
    if (definition_node == nullptr)
    {
        printf("I don't know what is %s.\n", second_entity);
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        printf("%s is %s\n", second_entity, second_entity);
        return TREE_NO_ERRORS;
    }

    Definition definition_second = {};
    createDefinition(&stack, definition_node, &definition_second);

    printf("Common between %s and %s:",
           first_entity,
           second_entity);

    int counter_first = definition_first.length - 1;
    int counter_second = definition_second.length - 1;

    while ((strcasecmp(
        definition_first.definition[counter_first],
        definition_second.definition[counter_second]) == 0)
        and counter_first >= 0
        and counter_second >= 0)
    {
        printf("%s%s",
               (counter_first == definition_first.length - 1) ? " "
                                                              : " and",
               definition_first.definition[counter_first]);

        counter_first--;
        counter_second--;
    }
    if (counter_first != definition_first.length - 1)
        printf(".\n");
    else
        printf(" nothing common...\n");

    printf("Difference between %s and %s:\n",
           first_entity,
           second_entity);

    if (counter_first>=0)
        printf("%s:", first_entity);
    for (int i = counter_first; i >= 0; i--)
    {
        printf("%s%s", definition_first.definition[i], i ? " and" : ".\n");
    }

    if (counter_second>=0)
        printf("%s:", second_entity);
    for (int i = counter_second; i >= 0; i--)
    {
        printf("%s%s", definition_second.definition[i], i ? " and" : ".\n");
    }
}

size_t getDefinition(Tree *tree, Val_t value)
{
    Stack stack = {};
    size_t error = STACK_NO_ERRORS;
    stackCtor(&stack, 0, &error)

    Node *definition_node = pushUntilValue(tree, &stack, value);

    if (definition_node == nullptr)
    {
        printf("I don't know what is it.\n");
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        printf("%s is %s\n", value, value);
        return TREE_NO_ERRORS;
    }
    printf("%s is", value);

    Definition definition = {};

    createDefinition(&stack, definition_node, &definition);

    for (int i = definition.length - 1; i >= 0; i--)
    {
        printf("%s%s", definition.definition[i], i ? " and" : ".\n");
    }

    return error;
}

Node *pushUntilValue(Tree *tree, Stack *stack, Val_t value)
{
    pushPointersToStack(tree->root, stack, value);
    if (stack->size == 0)
        return nullptr;

    Node *definition_node = nullptr;
    Elem_t stackValue = 0;
    while (stack->size)
    {
        stackPop(stack, &stackValue);
        if (strcasecmp(((Node *) stackValue)->value, value) == 0)
        {
            definition_node = (Node *) stackValue;
//            printf("%s is", value);
            break;
        }
    }
    return definition_node;
}

size_t createDefinition(Stack *stack,
                        Node *definition_node,
                        Definition *definition)
{
    Elem_t stackValue = 0;
    Node *candidate_definition_node = nullptr;

    while (stack->size)
    {
        stackPop(stack, &stackValue);
        candidate_definition_node = (Node *) stackValue;
        if (candidate_definition_node->left == definition_node)
        {
            definition_node = candidate_definition_node;
            sprintf(definition->definition[definition->length],
                    " %s",
                    definition_node->value);
            definition->length++;
            continue;
        }
        else if (candidate_definition_node->right == definition_node)
        {
            definition_node = candidate_definition_node;
            sprintf(definition->definition[definition->length],
                    " not %s",
                    definition_node->value);
            definition->length++;
            continue;
        }
    }

}

size_t pushPointersToStack(Node *node, Stack *stack, Val_t value)
{
    CHECK_NULLPTR_ERROR(node, NODE_IS_NULLPTR)
    CHECK_NULLPTR_ERROR(stack, STACK_NULLPTR)

    Elem_t stackValue = 0;

    stackPush(stack, (Elem_t) node);

    if (strcasecmp(node->value, value) == 0)
        return TREE_NO_ERRORS;

    if (node->left)
        pushPointersToStack(node->left, stack, value);
    if (node->right)
        pushPointersToStack(node->right, stack, value);
}
