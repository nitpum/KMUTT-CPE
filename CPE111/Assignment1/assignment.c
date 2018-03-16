#include <stdio.h>

int factorial (int n, int start) {
    int answer;
    if (n == 0)
    {
        printf("\n0! is base case return answer of 0! = 1");
        answer = 1;
    }
    else
    {
        printf("\n%d! is recursive case. Answer = %d * recursion of %d", n, n, n - 1);
        printf("\n   Recursion to calculate %d!", n - 1);
        answer = n * factorial(n - 1, start);
    }

    if (n != start)
    {
        printf("\nCalculate %d!complete.", n );
        printf("\n   Return answer from %d! = %d to calculate %d = [%d * %d!] = %d", n, answer, n + 1, n + 1, n, (n + 1) * answer);
    }
    else
    {
        printf("\nComplete calculation of %d!, answer = %d", start, answer);
    }

    return answer;
}

int main ()
{
    int n, buffer, max = 12;
    char again;
    do
    {
        printf("Factorial Recursion Program\nCalculate n! by Recursive function\n");
        rewind(stdin);
        printf("Enter n (n < %d): ", max + 1);
        while(scanf("%d%c", &n, &buffer) != 2 || buffer != '\n' || n >= 13 || n < 0)
        {
            rewind(stdin);
            printf("Error input. Please enter between 0 - %d", max);
            printf("\nEnter n (n < %d): ", max + 1);
        }
        factorial(n, n);
        rewind(stdin);
        printf("\nPress [y] to continue.");
        scanf("%c", &again);
    }
    while(again == 'y');

    printf("\n =====================\n");
    printf("End program.");
    printf("\nProgram by 60070501029 Nitipoom Unrrom");
    printf("\n =====================\n\n\n");

    return 0;
}
