#ifndef interpreter_h

#define interpreter_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

#define MAX_LINES 512 // todo: dynamic sizing?

#include "./parser.h"
#include "./scanner.h"
#include "./evals.h"


void initialize(void);
void addLine(int, char*);

#endif