#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    while (1) {
        printf("enter character: ");
        if (scanf("%d", &i) != 1) {
            printf("hi");
            while (getchar() != '\n');
        } else {
            char c = (char)i;
            if (c >= 0 && c <= 127) {
                printf("%d corresponds to: %c\n", i, c);
            } else if(c == -8) {
                system("clear");
            } else {
                printf("yeah");
            }
        }
    }

    return 0;
}
