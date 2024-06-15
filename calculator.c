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
    // 120.20 + 10 * log1 - 5.5 * pi / e + ln10
    for(int i=strlen(line); i>=0; i--)
    {
        if(line[i] == ' ') continue;
        else if(line[i] <= '9' && line[i] >= '0')
        {
            line[i+1] = '\0';
            int counter = 0;
            while((line[i] <= '9' && line[i] >= '0') || line[i] == '.')
            {
                counter++;
                i--;
            }
            addToStack(operands, line+i+1);
            line[i+1] = '\0';
            i++;
        }
        else if(line[i] == 'i' && line[i-1] == 'p')
        {
            i--;
            line[i] = '\0';
            addToStack(operands, "pi");
        }
        else if(line[i] == 'e')
        {
            line[i] = '\0';
            addToStack(operands, "e");
        }
        
        else if(line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/') 
        {
            printf("Eneterd for line[%d]=%c\n", i, line[i]);
            char temp[2];
            temp[0] = line[i];
            temp[1] = '\0';
            addToStack(operators, temp);
            line[i] = '\0';
        }
        else if(line[i] == 'n' && line[i-1] == 'l')
        {
            i--;
            line[i] = '\0';
            addToStack(operators, "ln");
        }
        else if(line[i] == 'g' && line[i-1] == 'o' && line[i-2] == 'l')
        {
            i-=2;
            line[i] = '\0';
            addToStack(operators, "log");
        }
        else {
            printf("Invalid character detected!\n");
            exit(1);
        }
    }
}


int main()
{
    char line[100];
    printf("Enter equation: ");
    fgets(line, 99, stdin);
    printf("%s\n", line);

    Stack* operands = createStack();
    Stack* operators = createStack();


    tokenize(line, operands, operators);
    int strinka = operands->size;
    int kaka = operators->size;
    for(int i=0; i<strinka; i++)
    {
        printf("%s\n", takeFromStack(operands));
    }
    printf("\n");
    for(int i=0; i<kaka; i++)
    {
        printf("%s\n", takeFromStack(operators));
    }

    return 0;
}