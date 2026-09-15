#include <stdio.h>
#include <math.h>

int main() {
    float a = sin(5);
    float *pA = &a;

    printf("%f", *(&a));
}
