#include <stdio.h>

int main() {
    int n = 0;
    while (n < 500) {
        n += n;
    }

    printf("%d", n);
}
