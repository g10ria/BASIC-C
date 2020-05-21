#include "../headers/evals.h"

int evaluateExp(struct expression *e)
{
    if (e->op == '\0') {
        char* var = get(e->exp2);

        // raw value, not a variable
        if (var==NULL) return atoi(e->exp2);
        
        return atoi(var);
    }
    else
    {
        int exp2 = atoi(e->exp2);
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

/**
 * Helper function, converts a number to a string
 */ 
char * numToString(int num) {
    int places = 0;
    
    int n = num;
    while(n != 0) {
        places++;
        n/=10;
    }

    char * res = malloc(places * sizeof(char));
    for(int i=places-1;i>=0;i--) {
        res[i] = num%10 + '0';
        num/=10;
    }

    return res;
}

void eval(struct statement* statements, int numStatements, int* lineToIndex) {
    initializeHashmap();

    struct statement *s = statements; // current statement

    for(int i=0;i<numStatements;i++) {

        switch(s->type) {
            case('R'):
                break;
            case('L'):;
                int value = evaluateExp(s->arg2.exp);
                put(s->arg1.str, numToString(3));
                break;
            case('P'):;
                int result = evaluateExp(s->arg1.exp);
                printf("%d\n", result);
                break;
            case('N'):;
                // waits for input
                break;
            case('G'):;
                int line = s->arg1.num;     // line 10
                int index = lineToIndex[line-1];
                printf("going to line %d and index %d\n", line, index);
                i = index - 1;
                s = statements + index - 1;
                break;
        }
        s++;
    }
}