#include "stdio.h"
#include "cstdlib"
#include <time.h>

int normalRandom (int minValue, int maxValue)
{
    return (minValue) + (rand() % ((maxValue + 1) - minValue));
}

int main ()
{
    srand(time(NULL));

    printf("Hi, let's play a number game !\n");

    int round = 0;
    int num, x;

    num = 1 + (rand() % 100);

    do
    {
        round += 1;
        printf("Round %d : enter a number \n", round);

        scanf("%d", &x);
        rewind(stdin);

        if (x == num)
            printf("Correct ! You win in round %d \n", round);
        else if (x < num)
            printf("Too low \n");
        else printf("Too high\n");
    }
    while(round != 7 && x != num);

    if (x != num)
        printf("You lose anwser is %d \n", num);

    return 0;
}