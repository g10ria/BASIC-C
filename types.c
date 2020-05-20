#ifndef PLACEHOLDER

#define PLACEHOLDER 0

struct expression
{
    struct expression *exp1;
    int exp2;
    char op;
};

union argument {
    char *str;
    int num;
    struct expression *exp;
};

// pseudo-polymorphism hehe
struct statement
{
    char type; // denotes the "subclass"

    union argument arg1;
    union argument arg2;
};

struct token
{
    char type;
    /**
     * k for keyword
     * v for varname
     * n for number
     * o for operand
     * e for end (no more tokens)
     */
    char *val;
};
#endif