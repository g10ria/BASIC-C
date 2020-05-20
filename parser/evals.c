#include "../headers/evals.h"

struct statement *s; // current statement

// void evaluateREM() {}
// void evaluateLET(statement) {

// }

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

void eval(struct statement* statements, int numStatements) {
    initializeHashmap();

    s = statements;
    for(int i=0;i<numStatements;i++) {
        switch(s->type) {
            case('R'):
                break;
            case('L'):;
                // arg1.str = varname
                // arg2
                int value = evaluateExp(s->arg2.exp);
                put(s->arg1.str, numToString(3));
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