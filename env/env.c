#include "../headers/env.h"

initializeEnv() {
    initializeHashmap();
}

addVar(char* name, char* value) {
    put(name, value);
}

getVar(char* name) {

    // test existence??
    return get(name);
}


