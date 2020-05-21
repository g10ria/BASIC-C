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

    // todo: refactor into actual methods lol
    initializeHashmap();

    struct statement *s = statements; // current statement
    int pause = 0;

    for(int i=0;i<numStatements;i++) {

        if (pause == 0) s = statements + i;
        else pause = 0;

        switch(s->type) {

            case('R'):  // REM
                s++;
                break;

            case('L'):; //LET
                int value = evaluateExp(s->arg2.exp);
                put(s->arg1.str, numToString(value));
                s++;
                break;

            case('P'):; // PRINT
                int result = evaluateExp(s->arg1.exp);
                printf("%d\n", result);
                s++;
                break;

            case('N'):; // (I)NPUT
                int answer = 0;
                scanf("%d", &answer);
                put(s->arg1.str, numToString(answer));
                break;

            case('G'):; // GOTO
                int line = s->arg1.num;
                int index = lineToIndex[line-1];
                i = index - 1;
                s = statements + index - 1;
                break;

            case('I'):;
                int left = evaluateExp(s->arg1.exp);
                int right = evaluateExp(s->arg3.exp);
                char op = *(s->arg2.str);

                int cond = 0;
                switch(op) {
                    case('='): cond = left == right; break;
                    case('<'): cond = left < right; break;
                    case('>'): cond = left > right; break;
                    default: printf("erororororo");
                }

                if (cond) {
                    s = s->arg4.sta;
                    i--;
                    pause = 1;
                }

                break;

            case('E'):  // end
                i = numStatements;

        }
    }
}