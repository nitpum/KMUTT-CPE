#include <stdio.h>
#include <time.h>

int main ()
{
    srand(time(NULL));
    int anwser, round = 0, playerInput;
    int win = 0;
    anwser = 1 + (rand() % 100);
    do
    {
        round += 1;
        printf("Guess number round %d\n", round);
        printf("Enter your guess number: ");
        scanf("%d", &playerInput);
        if (playerInput == anwser)
        {
            win = 1;
        } else if (playerInput < anwser)
        {
            printf("\nYou number is too low \n");
        } else
        {
            printf("\nYou number is too high \n");
        }

    } while (round < 7 && win == 0);

    if (win == 1)
    {
        printf("Correct ! you win in round %d", round);
    } else {
        printf("You lose ! and the anwser is %d", anwser);
    }

}
