#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    NUMBER,

    OP_ADD,
    OP_SUB,

    LEFT_PAREN,
    RIGHT_PAREN,

    INVALID
} token;

token tokenize(char c) {
    if (c >= '0' && c <= '9') {
        return NUMBER;
    }

    switch (c) {
    case '(':
        return LEFT_PAREN;
        break;

    case ')':
        return RIGHT_PAREN;
        break;

    case '+':
        return OP_ADD;
        break;

    case '-':
        return OP_SUB;
        break;
    }

    return INVALID;
}


int main(int argc, char **argv) {

    return 0;
}
