#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INITIAL_LINES 512   // todo: dynamic sizing?

#include "./parser/parser.c"
#include "./scanner/scanner.c"
#include "./parser/evals.c"

char** lines;       // array of the lines
int numLines = 0;
int* next;          // stores the next line of every line
int firstLine = NUM_INITIAL_LINES;

void initialize() {
    next = malloc(NUM_INITIAL_LINES * sizeof(int));
    for (int i = 0; i < NUM_INITIAL_LINES; i++) next[i] = -1;
    lines = malloc(NUM_INITIAL_LINES * sizeof(char *));
}

void addLine(int line, char* input)
{
    int spaceInd = 0;
    while(input[spaceInd] != ' ') spaceInd++;
    input = input + spaceInd + 1;

    if (line<firstLine) firstLine = line;
    numLines++; // todo fix

    lines[line] = input;

    /**
     * Updates the nextLines array (goes "down" the array
     * and updates "next values")
     */
    int nextValue = next[line];
    int currNextValue = nextValue;
    int currNextValueIndex = line;
    while (currNextValue == next[line] && currNextValueIndex > 0)
    {
        currNextValueIndex--;
        currNextValue = next[currNextValueIndex];
        next[currNextValueIndex] = line;
    }
}

int main() {
    initialize();

    char* input = "10 PRINT 3";
    char* input2 = "20 REM hello";

    int line = atoi(input);

    addLine(line, input);

    line = atoi(input2);
    addLine(line, input2);

    // printf("%d %d", next[0], next[20]);

    struct token* tokens = scan(lines, numLines, firstLine, next);
    struct statement* statements = parse(tokens, numLines);
    eval(statements, numLines);

    free(lines);
    free(next);

    return 0;
}