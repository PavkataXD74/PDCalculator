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
            printf("Invalid character detected!\n");
            exit(1);
        }
    }

    free(newLine);
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


    int operandsSize = operands->size;
    int operatorsSize = operators->size;
    for(int i=0; i<operandsSize; i++)
    {
        printf("%s\n", takeFromStack(operands));
    }
    printf("\n");
    for(int i=0; i<operatorsSize; i++)
    {
        printf("%s\n", takeFromStack(operators));
    }


    free(operands);
    free(operators);

    return 0;
}