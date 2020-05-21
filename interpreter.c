#include "./headers/interpreter.h"

char** lines;       // array of the lines
int numLines = 0;
int* next;          // stores the next line of every line
int firstLine = -1;

int* nextConverted;

int fakeNext[1] = {-1};
int fakeNextConverted[1] = {0};

void initialize() {
    next = malloc(MAX_LINES * sizeof(int));
    nextConverted = malloc(MAX_LINES * sizeof(int));
    for (int i = 0; i < MAX_LINES; i++)
        next[i] = -1;
    lines = malloc(MAX_LINES * sizeof(char *));
}

void addLine(char* input)
{
    int line = atoi(input);

    int spaceInd = 0;
    while(input[spaceInd] != ' ') spaceInd++;
    input = input + spaceInd + 1;

    if (firstLine==-1 || line<firstLine) firstLine = line;
    numLines++; // todo fix

    lines[line] = input;

    /**
     * Updates the nextLines array (goes "down" the array
     * and updates "next values")
     */
    int nextValue = next[line];
    int currNextValue = nextValue;
    int currNextValueIndex = line-1;
    
    while (currNextValue == next[line] && currNextValueIndex >= 0)
    {
        next[currNextValueIndex] = line;

        currNextValueIndex--;
        currNextValue = next[currNextValueIndex];
    }
}

int* convertLinesToIndex() {
    int current = 0;
    int previousNext = next[0];
    
    for(int i=0;i<MAX_LINES;i++) {
        
        if (next[i] != previousNext) {
            current++;
            previousNext = next[i];
        }
        // printf("%d goes to %d\n", i, current);
        nextConverted[i] = current;

        if (i<MAX_LINES-1 && next[i+1]==-1) break;
    }
}

void runProgram() {
    struct token *tokens = scan(lines, numLines, firstLine, next);
    struct statement *statements = parse(tokens, numLines);
    convertLinesToIndex();
    eval(statements, numLines, nextConverted);
}

void listProgram() {
    int nextLine = firstLine;

    while (nextLine != -1)
    {
        printf("%d %s\n", nextLine, lines[nextLine]);
        nextLine = next[nextLine];
    }
}

void clearProgram() {
    for(int i=0;i<MAX_LINES;i++) {
        next[i] = -1;
        lines[i] = NULL; // test
    }
    numLines = 0;
}

void printHelp() {

}

void quit() {
    exit(0);
}

int strLen(char * str) {
    int len = 0;
    while(str[len] != '\0') len++;
    return len+1;
}

void runImmediate(char* statement) {
    // int* temp =
    struct token *tokens = scan(&statement, 1, 0, fakeNext);
    struct statement *statements = parse(tokens, 1);
    // convertLinesToIndex();
    eval(statements, 1, fakeNextConverted);
}

#include <regex.h>
int match(const char *string, const char *pattern)
{
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0)
        return 0;
    return 1;
}

char * genImmediateRegex() {
    char *regex = "^PRINT ([a-zA-Z][a-zA-Z0-9_]*|[0-9]+)( [+\\-/*] ([a-zA-Z][a-zA-Z0-9_]*|[0-9]+))*$";

    // ([+\\-/*]([a-zA-Z][a-zA-Z0-9_]*|[0-9]+))*

    return regex;
}

// 

char * genRegex() {

    // // matches 1 expression
    // char *exp = "([a-zA-Z][a-zA-Z0-9_]*|[0-9]+)([+\\-/*]([a-zA-Z][a-zA-Z0-9_]*|[0-9]+))*";
    // int expLen = 70;

    // GET
    char * regex = "\
    ^GOTO [0-9]+$\
    ";

    return regex;
}

int main() {
    initialize();
    char *immediateRegex = genImmediateRegex();

    printf("Welcome to your simplified BASIC interpreter.\n\n\
    \tMAX PROGRAM LENGTH: %d lines\n\
    \tMAX LINE LENGTH: %d characters\n\
    \tUse CTRL-C to quit the interpreter.\n\n",
           MAX_LINES, MAX_LINE_LENGTH);

    char* l = malloc(MAX_LINE_LENGTH * sizeof(char));

    while (1==1) {
        scanf("%[^\n]%*c", l);
        // fgets(l, MAX_LINE_LENGTH, stdin);

        if (*l =='\0') continue; // skip empty lines

        if (strcmp(l, "RUN")==0) runProgram();
        else if (strcmp(l, "LIST")==0) listProgram();
        else if (strcmp(l, "CLEAR")==0) clearProgram();
        else if (strcmp(l, "HELP")==0) printHelp();
        else if (strcmp(l, "QUIT")==0) quit();
        else {
            // todo: check against regex

            // make a copy of the string
            // int length = strLen(l);
            // char * l2 = malloc(length * sizeof(char));
            // for(int i=0;i<length;i++) l2[i] = l[i];

            // addLine(l2);

            printf("Immediate: %s\n", immediateRegex);

            if (match(l, immediateRegex)) {
                printf("matched\n");
                runImmediate(l);
            }
        }        
    }

    free(lines);
    free(next);
    free(nextConverted);

    return 0;
}