struct expression
{
    struct expression *exp1;
    int exp2;
    char op;
};

union argument {
    char *str;
    int num;
    struct expression* exp;
};

// pseudo-polymorphism hehe
struct statement
{
    char type;      // denotes the "subclass"

    union argument arg1;
    union argument arg2;
};