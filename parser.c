#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

struct expression
{
    struct expression *exp1;
    int exp2; // child nodes
    char op;
    
};

/**
 * Strictly evaluates arithmetic expression left to right (unfortunately)
 */ 
struct expression * parseExpression(char *inp, int length)
{
    struct expression* e = malloc(sizeof(struct expression));

    int opIndex = length-1;

    // it is a digit
    while (isdigit(inp[opIndex])!=0 && opIndex>0)
    {
        opIndex--;
    }

    if (opIndex == 0)
    {
        e->exp2 = atoi(&(inp[opIndex]));
        e->op = '\0';
        return e;
    }
    else
    {
        e->exp2 = atoi(&(inp[opIndex + 1]));
        e->op = inp[opIndex];
        struct expression * e2 = parseExpression(inp, opIndex);
        e->exp1 = e2;
        
        return e;
    } 
}

int evaluate(struct expression * e) {

    int exp2 = e->exp2;
    if (e->op == '\0')
        return exp2;
    else
    {
        int exp1 = evaluate(e->exp1);
        
        switch (e->op)
        {
        case ('+'):
            return exp1 + exp2;
        case ('*'):
            return exp1 * exp2;
        case ('-'):
            return exp1 - exp2;
        case ('/'):
            return exp1 / exp2;
        default:
            printf("errorrrr");
        }
    }

    
}

int main() {
    char* inp = "32-33+5+6";

    struct expression * e = parseExpression(inp, 8);

    printf("%d", evaluate(e));    
}

