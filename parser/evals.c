#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#include "../types.c"

struct statement *s; // current statement

// void evaluateREM() {}
// void evaluateLET(statement) {

// }

int evaluateExp(struct expression *e)
{
    int exp2 = e->exp2;

    if (e->op == '\0') return exp2;
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

void eval(struct statement* statements, int numStatements) {
    s = statements;
    for(int i=0;i<numStatements;i++) {
        switch(s->type) {
            case('R'):
                break;
            case('L'):
                // set a variable (let's just ignore this for now lol)
                break;
            case('P'):
                ;
                int result = evaluateExp(s->arg1.exp);
                printf("%d\n", result);
                break;
        }
        s++;
    }
}