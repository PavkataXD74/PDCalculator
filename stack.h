#ifndef STACK_H
#define STACK_H

struct stackNode
{
    struct stackNode* lastElem;
    double value;
};

typedef struct
{
    struct stackNode* stackHead;
    unsigned int size;
} Stack;



Stack* createStack();
struct stackNode* createStackNode(double value);
void addToStack(Stack* stack, double value);
double takeFromStack(Stack* stack);

#endif