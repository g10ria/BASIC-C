#ifndef evals_h

#define evals_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

// #include "./env.h"
#include "../hashmap/headers/hashmapLite.h"

int evaluateExp(struct expression*);

void eval(struct statement*, int);

#endif