#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "../types.c"

struct token* t; // current token

/**
 * Strictly evaluates arithmetic expression left to right (unfortunately)
 */ 
struct expression* parseExpression(char *inp, int length)
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
        struct expression* e2 = parseExpression(inp, opIndex);
        e->exp1 = e2;
        
        return e;
    } 
}

int evaluateExp(struct expression * e) {

    int exp2 = e->exp2;
    if (e->op == '\0')
        return exp2;
    else
    {
        int exp1 = evaluateExp(e->exp1);

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

void parseStatement() {
    struct statement *s = malloc(sizeof(struct statement));
    s->type = (t->val)[0];

    t++;

    union argument arg1;
    union argument arg2;

    switch (s->type)
    {
        case ('R'): // REM
            arg1.str = t->val;
            t++;

            printf("%s\n", arg1.str);
            break;

        case('L'):  // LET FIX THIS LOL
            arg1.str = t->val;
            t+=2; // skip the '='
            arg2.str = t->val;
            t++;

            printf("%s %s\n", arg1.str, arg2.str);
            break;
    }
}

void parse(struct token* tokens) {
    t = tokens;

    // parse a program
    while(t->type != 'e')
    {
        parseStatement(t);       
    }
}

// int main() {
//     // lil tester
//     char* inp = "LET x = 3";

//     parseStatement(inp);

//     /**
//      * rem, let, print, input, goto, if, end
//      */

//     // struct expression * e = parseExpression(inp, 8);

//     // printf("%d", evaluateExp(e));
//     return 0;
// }

