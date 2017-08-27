#include <stdio.h>
#include <time.h>

int main ()
{
    srand(time(NULL));
    int anwser, round, win, playerAnwser, endCheck, invalidInput;
    char playAgain, playerInput;
    char playerName[20];

    // Introduce Program
    printf("Hello ! This is a guess number game");
    printf("\nWhat's your name ? (Max character: 20) : ");
    // Ask player name
    do
    {
        fgets(playerName, 20, stdin);
        int i = 0;
        for (; i < 20;i++)
        {
            if (playerName[i] == '\n')
            {
                playerName[i] = '\0';
            }
        }
    }
    while(playerName[0] == '\0');
    printf("Hi %s ! \n", playerName);

    // Play guess number game
    do
    {
        rewind(stdin);

        anwser = 1 + (rand() % 100);

        // Reset
        round = 0;
        win = 0;
        playerAnwser = 0;

        // Round
        do
        {
            round += 1;
            printf("%s guess number round %d between 1 - 100\n", playerName, round);
            printf("Enter your guess number: ");

            // Get input
            do
            {
                endCheck = 0;
                invalidInput = 0;
                playerAnwser = 0;
                playerInput = 0;
                while(endCheck == 0)
                {
                    playerInput = getchar();
                    if ((playerInput >= '0' && playerInput <= '9' ) || playerInput == '\n')
                    {
                        if (playerInput == '\n')
                        {
                            if (playerAnwser >= 1 && playerAnwser <= 100)
                                endCheck = 1;
                            else invalidInput = 1;
                        } else {
                            playerAnwser = (playerAnwser * 10) + (playerInput - '0');
                        }
                    } else {
                        invalidInput = 1;
                    }

                    if (invalidInput)
                    {
                        printf("Invalid input ! Please enter number between 1 - 100\n");
                        endCheck = 1;
                    }
                }
                rewind(stdin);
            }
            while(invalidInput == 1);

            if (playerAnwser == anwser)
            {
                win = 1;
            } else if (playerAnwser < anwser)
            {
                printf("\nHey %s ! number is too low \n", playerName);
            } else
            {
                printf("\nHey %s ! number is too high \n", playerName);
            }
        }
        while (round < 7 && win == 0);

        if (win == 1)
        {
            printf("Correct %s ! you win in round %d", playerName, round);
        } else {
            printf("You lose %s ! and the anwser is %d", playerName, anwser);
        }

        printf("\nDo you want to play again ? [Y/n] \n");
        scanf("%c", &playAgain);
        while(playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')
        {
            printf("Invalid input ! Please enter Y or N \n");
            scanf("%c", &playAgain);
            rewind(stdin);
        }
    }
    while(playAgain == 'y' || playAgain == 'Y');

}
