#ifndef STACK_H
#define STACK_H

struct stackNode
{
    struct stackNode* lastElem;
    char* value;
};

typedef struct
{
    struct stackNode* stackHead;
    unsigned int size;
} Stack;



Stack* createStack();
struct stackNode* createStackNode(char* value);
void addToStack(Stack* stack, char* value);
char* takeFromStack(Stack* stack);

#endif