#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_INITIAL_LINES 512   // todo: dynamic sizing

char** lines;       // array of the lines
int* next;     // stores the next line of every line

typedef struct
{
    node* children; // child nodes
    char *key; // unhashed key as a string
    char *val; // type as a raw string

} node;

void initialize() {
    next = malloc(NUM_INITIAL_LINES * sizeof(int));
    for (int i = 0; i < NUM_INITIAL_LINES; i++) next[i] = -1;
    lines = malloc(NUM_INITIAL_LINES * sizeof(char *));
}

void addLine(int line, char* input)
{
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

    char* input = "10 HELLO CONTENT";

    int line = atoi(input);

    addLine(line, input);

    printf("%d %d", next[0], next[20]);

    free(lines);
    free(next);

    return 0;
}