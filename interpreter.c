#include "./headers/interpreter.h"

char** lines;       // array of the lines
int numLines = 0;
int* next;          // stores the next line of every line
int firstLine = MAX_LINES;

void initialize() {
    next = malloc(MAX_LINES * sizeof(int));
    for (int i = 0; i < MAX_LINES; i++)
        next[i] = -1;
    lines = malloc(MAX_LINES * sizeof(char *));
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

    char *input = "20 LET x = 3";
    char* input2 = "30 PRINT 5";

    int line = atoi(input);

    addLine(line, input);

    line = atoi(input2);
    addLine(line, input2);

    struct token* tokens = scan(lines, numLines, firstLine, next);
    struct statement* statements = parse(tokens, numLines);
    eval(statements, numLines);

    free(lines);
    free(next);

    return 0;
}