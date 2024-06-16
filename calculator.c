#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "stack.h"

#define PI 3.14159265358979323846
#define E 2.71828182845904523536


double sum(double a, double b)
{
    return a+b;
}

double subtract(double a, double b)
{
    return a-b;
}

double multiply(double a, double b)
{
    return a*b;
}

double divide(double a, double b)
{
    /*if(b == 0) {
        printf("Division by zero detected!!!!");
        exit(1);
    }*/
    return a/b;
}

double ln(double a)
{
    return log(a);
}

double logBase(double a, double b)
{
    return log(a) / log(b);
}

double pi()
{
    return PI;
}

double e()
{
    return E;
}


void tokenize(char* line, Stack* operands, Stack* operators)
{
    char* newLine = calloc(strlen(line)+1, sizeof(char));
    strcpy(newLine, line);

    // 120.20 + 10 * log1 - 5.5 * pi / e + ln10
    for(int i=strlen(newLine); i>=0; i--)
    {
        if(newLine[i] == ' ') continue;
        else if(newLine[i] <= '9' && newLine[i] >= '0')
        {
            newLine[i+1] = '\0';
            int counter = 0;
            while((newLine[i] <= '9' && newLine[i] >= '0') || newLine[i] == '.')
            {
                counter++;
                i--;
            }
            addToStack(operands, newLine+i+1);
            newLine[i+1] = '\0';
            i++;
        }
        else if(newLine[i] == 'i' && newLine[i-1] == 'p')
        {
            i--;
            newLine[i] = '\0';
            addToStack(operands, "pi");
        }
        else if(newLine[i] == 'e')
        {
            newLine[i] = '\0';
            addToStack(operands, "e");
        }
        
        else if(newLine[i] == '+' || newLine[i] == '-' || newLine[i] == '*' || newLine[i] == '/') 
        {
            char temp[2];
            temp[0] = newLine[i];
            temp[1] = '\0';
            addToStack(operators, temp);
            newLine[i] = '\0';
        }
        else if(newLine[i] == 'n' && newLine[i-1] == 'l')
        {
            i--;
            newLine[i] = '\0';
            addToStack(operators, "ln");
        }
        else if(newLine[i] == 'g' && newLine[i-1] == 'o' && newLine[i-2] == 'l')
        {
            i-=2;
            newLine[i] = '\0';
            addToStack(operators, "log");
        }
        else if(newLine[i] != '\0'){
            printf("Invalid syntax!\nAt character number %d:\n", i+1);
            printf("Unrecognized \"%c\"\n", newLine[i]);
            printf("%s\n", line);
            while(i > 0)
            {
                i--;
                printf(" ");
            }
            printf("^\n");
            exit(1);
        }
    }

    free(newLine);
}

int isValidNumber(char* number){
    if(number[0] == '.') return 0;
    int lettersInNumber = 0;
    int afterDot = 0;
    int dotCount = 0;
    for(int i = 0; i < strlen(number); i++){
        if(number[i] == '.'){
            dotCount ++;
            if(dotCount > 1){
                return 0;
            }
        }else if(number[i] <= '9' && number[i] >= '0' && dotCount == 1){
            afterDot = 1;
        }else if(number[i] <= '9' && number[i] >= '0'){
            continue;
        }else{
            lettersInNumber = 1;
            break;
        }
    }
    // printf("dotCount: %d; afterDot: %d; lettersInNumber:%d\n", dotCount, afterDot, lettersInNumber);
    if((dotCount == 1 && afterDot == 1 && lettersInNumber == 0) || (dotCount == 0 && afterDot == 0 && lettersInNumber == 0)){
        return 1;
    }
    return 0;
}

int validateEquation(Stack* operands, Stack* operators){
    int operandsCount = operands->size;
    int operatorsCount = operators->size;

    struct stackNode* currentNode = operands->stackHead;
    int treversedNodes = 0;
    while(currentNode != NULL){
        int flag = isValidNumber(currentNode->value);
        if(flag == 0){
            return treversedNodes;
        }else if(flag == 1){
            treversedNodes++;
            currentNode = currentNode->lastElem;
        }
    }

    currentNode = operators->stackHead;
    while(currentNode != NULL){
        if(strcmp(currentNode->value, "+") == 0 || 
           strcmp(currentNode->value, "-") == 0 || 
           strcmp(currentNode->value, "*") == 0 || 
           strcmp(currentNode->value, "/") == 0 || 
           strcmp(currentNode->value, "log") == 0)
        {
            operandsCount--;
            operatorsCount--;
        }else if(strcmp(currentNode->value, "ln") == 0){
            operatorsCount--;
        }else{
            printf("Invalid operation!\n");
            exit(1);
        }
        currentNode = currentNode->lastElem;
    }
    if(operandsCount == 1 && operatorsCount == 0){
        printf("Valid Equation\n");
        return -1;
    }else{
        printf("Invalid Equation! ");
        if(operandsCount > operatorsCount){
            printf("Not enough operators!\n"); 
        }else if(operandsCount <= operatorsCount){
            printf("Too many operators!\n"); 
        }
        return -2;
    }
}


int main()
{
    char line[100];
    printf("Enter equation: ");
    fgets(line, 99, stdin);
    if(strlen(line) == 1) {
        printf("Equasion cannot be empty!");
        return 1;
    }
    line[strlen(line)-1] = '\0';
    //printf("%s\n", line);


    Stack* operands = createStack();
    Stack* operators = createStack();

    tokenize(line, operands, operators);


    // int operandsSize = operands->size;
    // int operatorsSize = operators->size;
    // for(int i=0; i<operandsSize; i++)
    // {
    //     printf("%s\n", takeFromStack(operands));
    // }
    // printf("\n");
    // for(int i=0; i<operatorsSize; i++)
    // {
    //     printf("%s\n", takeFromStack(operators));
    // }

    int errorFlag = validateEquation(operands, operators);
    if(errorFlag == -2){
        return 1;
    }else if(errorFlag == -1){
        //calculate
    }else if(errorFlag >= 0){
        struct stackNode* currentNode = operands->stackHead;
        for(int i = 0; i < errorFlag; i++){
            currentNode =currentNode->lastElem;
        }
        printf("Your equation: %s\n", line);
        printf("Invalid operator at: %s\n", currentNode->value);
        return 1;
    }

    return 0;
}