#include <stdio.h>

int main ()
{
    int n = 44, i, sum = 0, f0 = 0, f1 = 1;
    for (i = 1; i < n; i++) {
        sum = f0 + f1;
        f0 = f1;
        f1 = sum;
    }
    printf("result: %d", sum);
    return 0;
}
