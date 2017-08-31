#include <stdio.h>
#include <math.h>

int main ()
{
    double angle, u, x, t;
    double ux, uy, ty, airTime;
    double r, h, sy, sx;
    double g = 9.81;

    printf("Velocity: ");
    scanf("%lf", &u);
    printf("Angle: ");
    scanf("%lf", &angle);
    printf("Distance: ");
    scanf("%lf", &x);

    r = angle * M_PI / 180.0;

    uy = u * sin(r);
    ux = u * cos(r);
    ty = uy / g;
    airTime = 2 * (ty);
    sy = pow(uy, 2)/( 2 * g);
    sx = ux * airTime;

    printf("====== RESULT ======");
    printf("\nHeightest: %lf", sy);
    printf("\nFar distance: %lf", sx);
    printf("\nTime: %lf", airTime);

    double gx, gy, gt;
    gt = x/ux;
    gy = uy * gt + 0.5 * (-g) * pow(gt, 2);

    if (gy > 0 && gt > 0)
        printf("\nHeight at goal line %lf m in %lf s", gy, gt);

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



    return 0;
}
