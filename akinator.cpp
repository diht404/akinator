#include "akinator.h"

bool VOICE_OUTPUT = false;

void setVoiceOutput()
{
    VOICE_OUTPUT = true;
}

void disableVoiceOutput()
{
    VOICE_OUTPUT = false;
}

size_t selectTask(Tree *tree)
{
    outputText("Hi, my name is Skynet. "
               "I an General Artificial Intelligence.\n");
    while (true)
    {
        int task = 0;

        outputText("Please, select a task:\n"
                   "0 exit.\n"
                   "1 guessing.\n"
                   "2 definition.\n"
                   "3 comparison.\n"
                   "4 dump.\n"
                   "5 save changes.\n");

        int correct = scanf("%d", &task);
        int readCount = 1;

        while (correct != 1 && readCount < 5)
        {
            outputText("Incorrect number, try again!\n");

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
                outputText("Good bye!\n");

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

                outputText("Definition of what you want?\n");

                skipUnusedSymbols();
                size_t len = gets(buffer);
                buffer[len - 1] = '\0';
                getDefinition(tree, buffer);
                break;
            }
            case 3:
            {
                outputText("Comparison of what you want?\n");

                char first_entity[BUFFER_SIZE] = "";

                outputText("Enter first entity: \n");

                skipUnusedSymbols();
                size_t first_len = gets(first_entity);
                first_entity[first_len - 1] = '\0';

                char second_entity[BUFFER_SIZE] = "";

                outputText("Enter second entity: \n");

                size_t second_len = gets(second_entity);
                second_entity[second_len - 1] = '\0';

                getComparison(tree, first_entity, second_entity);
                break;
            }
            case 4:
            {
                outputText("Tree dumped.\n");
                treeDump(tree);
                break;
            }
            case 5:
            {
                FILE *fp = fopen(AKINATOR_FILE, "w");
                treePrint(tree, fp);
                fclose(fp);
                outputText("Changes were saved.\n");
                break;
            }
            default:
            {
                outputText("Unknown command code: %d.\n", task);

                break;
            }
        }
    }
}

size_t treeGuessing(Tree *tree)
{
    CHECK_NULLPTR_ERROR(tree, TREE_IS_NULLPTR)

    char answer[BUFFER_SIZE] = "";
    outputText("Please make a word.\n");

    Node *current_node = tree->root;
    while (current_node->left != nullptr
        and current_node->right != nullptr)
    {
        outputText("%s?\n", current_node->value);

        outputText("Please answer yes or no.\n");

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
            outputText("I do not understand, try again.\n");
        }
    }
    outputText("%s?\n", current_node->value);

    outputText("Please answer yes or no.\n");

    scanf("%s", answer);

    if (strcasecmp(answer, "yes") == 0)
    {
        outputText("I told you I would guess!\n");
    }
    else if (strcasecmp(answer, "no") == 0)
    {
        char correct_answer[BUFFER_SIZE] = "";
        skipUnusedSymbols();

        outputText("What is the correct answer?\n");
        size_t correct_answer_size = gets(correct_answer);
        correct_answer[correct_answer_size - 1] = '\0';

        char delimiter_answer[BUFFER_SIZE] = "";

        outputText("I do not understand "
                   "that is the difference between \"%s\" and \"%s\". "
                   "Can you please explain?\n",
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
        outputText("It is the same. What do you want you compare?\n");
        return TREE_NO_ERRORS;
    }

    Stack stack = {};
    size_t error = STACK_NO_ERRORS;
    stackCtor(&stack, 0, &error)

    Node *definition_node = pushUntilValue(tree, &stack, first_entity);
    if (definition_node == nullptr)
    {
        outputText("I do not know what is %s.\n", first_entity);
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        outputText("%s is %s\n", first_entity, first_entity);
        return TREE_NO_ERRORS;
    }

    Definition definition_first = {};
    createDefinition(&stack, definition_node, &definition_first);

    definition_node = pushUntilValue(tree, &stack, second_entity);
    if (definition_node == nullptr)
    {
        outputText("I do not know what is %s.\n", second_entity);
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        outputText("%s is %s\n", second_entity, second_entity);
        return TREE_NO_ERRORS;
    }

    Definition definition_second = {};
    createDefinition(&stack, definition_node, &definition_second);

    outputText("Common between %s and %s:",
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
        outputText("%s%s",
                   (counter_first == definition_first.length - 1)
                   ? " "
                   : " and",
                   definition_first.definition[counter_first]);

        counter_first--;
        counter_second--;
    }
    if (counter_first != definition_first.length - 1)
        outputText(".\n");
    else
    {
        outputText(" nothing common...\n");
    }

    outputText("Difference between %s and %s:\n",
               first_entity,
               second_entity);

    if (counter_first >= 0)
    {
        outputText("%s:", first_entity);
    }
    for (int i = counter_first; i >= 0; i--)
    {
        outputText("%s%s",
                   definition_first.definition[i],
                   i ? " and" : ".\n");
    }

    if (counter_second >= 0)
    {
        outputText("%s:", second_entity);
    }
    for (int i = counter_second; i >= 0; i--)
    {
        outputText("%s%s",
                   definition_second.definition[i],
                   i ? " and" : ".\n");
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
        outputText("I do not know what is it.\n");
        return TREE_NO_ERRORS;
    }
    if (stack.size == 0)
    {
        outputText("%s is %s\n", value, value);
        return TREE_NO_ERRORS;
    }
    outputText("%s is", value);

    Definition definition = {};

    createDefinition(&stack, definition_node, &definition);

    for (int i = definition.length - 1; i >= 0; i--)
    {
        outputText("%s%s",
                   definition.definition[i],
                   i ? " and" : ".\n");
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

void outputText(const char *formatString, ...)
{
    assert(formatString != nullptr);

    va_list args = {};

    va_start(args, formatString);
    vprintf(formatString, args);
    va_end(args);
    if (!VOICE_OUTPUT)
        return;

    va_start(args, formatString);
    char commandFormatString[BUFFER_SIZE] = "";
    sprintf(commandFormatString,
            "echo "
            "%s"
            " | festival --tts",
            formatString);

    char command[BUFFER_SIZE] = "";
    vsprintf(command,
             commandFormatString,
             args);
    va_end(args);

    for (size_t i = 0; i < BUFFER_SIZE; i++)
    {
        if (command[i] == '\'' or
            command[i] == '\"' or
            command[i] == '\n' or
            command[i] == '\r' or
            command[i] == '\t')

            command[i] = ' ';
    }
    system(command);
}
