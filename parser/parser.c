#include "../headers/parser.h"

struct token* t; // current token

/**
 * Strictly evaluates arithmetic expression left to right (unfortunately)
 */ 
struct expression* parseExpression(char *inp, int length)
{
    // printf("parsing expression %s\n", inp);

    struct expression* e = malloc(sizeof(struct expression));
    
    int opIndex = length - 1;

    // it is a digit
    while (isdigit(inp[opIndex])!=0 && opIndex>0)
    {
        opIndex--;
    }

    if (opIndex == 0)
    {
        e->exp2 = &(inp[opIndex]);
        e->op = '\0';

        return e;
    }
    else
    {
        e->exp2 = &(inp[opIndex + 1]);
        e->op = inp[opIndex];
        struct expression* e2 = parseExpression(inp, opIndex);
        e->exp1 = e2;
        
        return e;
    } 
}

struct statement* parseStatement() {
    struct statement *s = malloc(sizeof(struct statement));
    s->type = (t->val)[0];

    // printf("parsing statement with first token %s\n", t->val);

    t++;

    union argument arg1;
    union argument arg2;
    union argument arg3;
    union argument arg4;

    // rem, let, print, nput, goto, if, end
    switch (s->type)
    {
        case ('R'): // REM
            arg1.str = t->val;
            t++;
            break;

        case('L'):  // LET 
            arg1.str = t->val;
            t+=2; // skip the '='

            int len = 0;
            while (t->val[len] != '\0')
                len++;
            arg2.exp = parseExpression(t->val, len);
            t++;
            break;
        
        case('P'):  // PRINT
            ;

            // printf("parsing print\n");
            int len2 = 0;
            while (t->val[len2] != '\0')
                len2++;
            arg1.exp = parseExpression(t->val, len2);

            t++;
            break;

        case('N'):  //  (I)NPUT
            arg1.str = t->val;
            t++;
            break;
        
        case('G'):  // GOTO
            arg1.num = atoi(t->val); // test if this works
            t++;
            break;

        // ughhhhhhhh
        case('I'):;
            // THIS NEEDS TESTING

            // todo: REFACTOR THIS
            int len4 = 0;
            while (t->val[len4] != '\0') len4++;
            arg1.exp = parseExpression(t->val, len4);
            t++;
            arg2.str = t->val;
            t++;

            int len5 = 0;
            while (t->val[len5] != '\0')
                len5++;
            arg3.exp = parseExpression(t->val, len5);
            t++;

            arg4.sta = parseStatement();

            break;

        case('E'):
            break;
    }

    s->arg1 = arg1;
    s->arg2 = arg2;
    s->arg3 = arg3;
    s->arg4 = arg4;

    return s;
}

struct statement* parse(struct token *tokens, int numStatements)
{
    t = tokens;

    struct statement *s = malloc(numStatements * sizeof(struct statement));
    int currStatement = 0;

    // parse a program
    while (currStatement < numStatements)
    {
        s[currStatement] = *parseStatement();
        currStatement++;
    }

    return s;
}