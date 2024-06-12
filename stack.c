#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


Stack* createStack()
{
    Stack* stack = malloc(sizeof(Stack*));

    stack->size = 0;
    stack->stackHead = NULL;

    return stack;
}

struct stackNode* createStackNode(double value)
{
    struct stackNode* node = malloc(sizeof(struct stackNode));

    node->value = value;
    node->lastElem = NULL;

    return node;
}

void addToStack(Stack* stack, double value)
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

double takeFromStack(Stack* stack)
{
    if(stack->size == 0) {
        printf("Stack is empty!\n");
        exit(1);
    }
    if(stack->size == 1) {
        double temp = stack->stackHead->value;
        stack->size--;
        free(stack->stackHead);
        return temp;
    }

    double temp = stack->stackHead->value;
    struct stackNode* oldHead = stack->stackHead;
    stack->stackHead = stack->stackHead->lastElem;
    stack->size--;

    free(oldHead);
    return temp;

}