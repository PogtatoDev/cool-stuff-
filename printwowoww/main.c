#include <stdio.h>
#include <unistd.h>

size_t Yeah_strlen(const char *str) {
    size_t idx = 0;
    char cursor = *str;

    while (cursor != 0) {
        idx++;
        cursor = str[idx];
    }

    return idx;
}

void Yeah_print(const char *output) {
    for (int i = 0; i < Yeah_strlen(output); i++) {
        write(1, output + i, 1);
    }
}

void Yeah_printf(const char *output) {
}

int main() {
    Yeah_print("helloguys");
    return 0;
}
