#include <stdio.h>
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


void removeChar(char *str, char c) {
    int len = strlen(str);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }

    str[j] = '\0';
}


int main()
{
    char line[100];
    printf("Enter equation: ");
    fgets(line, 99, stdin);
    removeChar(line, ' ');
    printf("%s\n", line);
    

    return 0;
}