#include <stdio.h>
#include <math.h>
#include <conio.h>

int main ()
{
    double angle, u, x, t;
    double ux, uy, ty, airTime;
    double r, h, sy, sx;
    double g = 9.81;
    char playAgain;

    do
    {

        printf("Velocity (m/s): ");
        scanf("%lf", &u);
        printf("Angle (degree): ");
        scanf("%lf", &angle);
        printf("Distance (m): ");
        scanf("%lf", &x);

        r = angle * M_PI / 180.0;

        uy = u * sin(r);
        ux = u * cos(r);
        ty = uy / g;
        airTime = 2 * (ty);
        sy = pow(uy, 2)/( 2 * g);
        sx = ux * airTime;

        printf("====== RESULT ======");
        printf("\nHeightest: %gm", sy);
        printf("\nFar distance: %gm", sx);
        printf("\nTime: %gs", airTime);


        double gx, gy, gt;
        gt = x/ux;
        gy = uy * gt + 0.5 * (-g) * pow(gt, 2);

        if (gy > 0 && gt > 0)
            printf("\nHeight at goal line %gm in %gs", gy, gt);

        if (gt <= 0.5 && gy < 2.44 && gy > 0)
        {
            printf("\n GOAL ! ");
        } else {
            if (gy < 2.44 && gy > 0)
                printf("\nGoal keeper get the ball");
            else if (gy >= 2.44)
                printf("\nBall over the goal");
            else printf("\nBall fall to the ground before reach goal");
            printf("\n NOT GOAL");
        }

        printf("\nDo you want to play again ? [Y/n]: ");
        scanf("%c", &playAgain);
        while(playAgain != 'y' && playAgain != 'Y' && playAgain != 'n' && playAgain != 'N')
        {
            printf("\nInvalid input ! Please enter Y or N");
            scanf("%c", &playAgain);
            rewind(stdin);
        }
    } while(playAgain == 'y' || playAgain == 'Y');


    return 0;
}
