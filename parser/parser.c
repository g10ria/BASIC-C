#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "../types.c"

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

void parseStatement(char* inp) {
    struct statement *s = malloc(sizeof(struct statement));
    s->type = (char)inp[0];

    // strip out the command
    int spaceInd = 0;
    while(inp[spaceInd]!=' ') spaceInd++;
    inp = inp + spaceInd + 1;

    union argument arg1;
    union argument arg2;

    switch (s->type)
    {
        case ('R'): // REM
            arg1.str = inp;
            break;
        case('L'):  // LET
            ;
            int spaceInd2 = 0;
            while(inp[spaceInd2]!=' ') spaceInd2++;

            // definitely test this lmaoo
            arg1.str = malloc(spaceInd2 + 1); // size + 1
            memcpy(arg1.str, inp, spaceInd2);
            arg1.str[spaceInd2] = '\0';

            int spaceInd3 = 0;
            while(inp[spaceInd3]!=' ') spaceInd3++;

            arg2.str = inp + spaceInd3 + 1;

            printf("%s\n", arg2.str);
            break;
    }
}

void parse(struct token* tokens) {
    int index = 0;
    struct token* t = tokens;

    while(t->type != 'e')
    {
        printf("%c %s\n", t->type, t->val);

        index++;
        t = tokens + index;
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

