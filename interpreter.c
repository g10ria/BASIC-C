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
        next[i] = current;

        if (i<MAX_LINES-1 && next[i+1]==-1) break;
    }
}

int main() {
    initialize();

    char *input = "30 GOTO 50";
    char* input2 = "40 PRINT 1";
    char* input3 = "50 PRINT 2";

    int line = atoi(input);
    addLine(line, input);
    line = atoi(input2);
    addLine(line, input2);
    line = atoi(input3);
    addLine(line, input3);

    struct token* tokens = scan(lines, numLines, firstLine, next);
    struct statement* statements = parse(tokens, numLines);
    convertLinesToIndex();
    eval(statements, numLines, next);

    free(lines);
    free(next);

    return 0;
}