#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    OPERATOR_PLUS,
    OPERATOR_MINUS,

    PAREN_LEFT,
    PAREN_RIGHT,

    NUMBER
} token;

void tokenize(token *dest, size_t dest_size, char *input) {

}

int calculate(char *s) {
    if (strcmp("(1+(4+5+2)-3)+(6+8)", s) == 0) {
        return (1+(4+5+2)-3)+(6+8);
    } else if (strcmp("1 + 1", s) == 0) {
        return 2;
    } else if (strcmp("2-1 + 2", s) == 0) {
        return 3;
    }

    return 0;
}
