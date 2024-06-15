#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


Stack* createStack()
{
    Stack* stack = malloc(sizeof(Stack*));

    stack->size = 0;
    stack->stackHead = NULL;

    return stack;
}

struct stackNode* createStackNode(char* value)
{
    struct stackNode* node = malloc(sizeof(struct stackNode));
    node->value = calloc(strlen(value) + 1, sizeof(char));

    strcpy(node->value, value);
    node->lastElem = NULL;

    return node;
}

void addToStack(Stack* stack, char* value)
{
    struct stackNode* newNode = createStackNode(value);

    stack->size++;
    if(stack->size == 1) {
        stack->stackHead = newNode;
        return;
    }

    newNode->lastElem = stack->stackHead;
    stack->stackHead = newNode;
}

char* takeFromStack(Stack* stack)
{
    if(stack->size == 0) {
        printf("Stack is empty!\n");
        exit(1);
    }
    if(stack->size == 1) {
        char* temp = calloc(strlen(stack->stackHead->value)+1, sizeof(char));
        strcpy(temp, stack->stackHead->value);
        stack->size--;
        free(stack->stackHead->value);
        free(stack->stackHead);
        return temp;
    }

    char* temp = calloc(strlen(stack->stackHead->value)+1, sizeof(char));
    strcpy(temp, stack->stackHead->value);
    struct stackNode* oldHead = stack->stackHead;
    stack->stackHead = stack->stackHead->lastElem;
    stack->size--;

    free(oldHead->value);
    free(oldHead);
    return temp;

}