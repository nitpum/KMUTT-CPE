#include <stdio.h>
#include <math.h>

double diff(double a, double b, double c);
double Newton_Raphson (double a, double b, double c, double *Xn);
double getdouble ();


int main ()
{
    int a, b, c, times;
    double x;
    printf("Calculator (ax^2 + bx + c)/ 2ax+b \n");
    printf("Enter a: "); a = getdouble();
    printf("Enter b: "); b = getdouble();
    printf("Enter c: "); c = getdouble();
    times = Newton_Raphson(a, b, c, &x);
    printf("==> %d \n", times);
    if (times == 0)
        printf("Error ! Can't find anwser");
    else printf("Your anwser is : %g", x);

    return 0;
}

double getdouble () {
    int endCheck, invalid, decimalIndex, negative;
    char input;
    double num;
    do
    {
        rewind(stdin);

        endCheck = 0;
        invalid = 0;
        decimalIndex = 0;
        num = 0.0;
        int added = 0;
        while (endCheck == 0 && invalid == 0)
        {
            input = getchar();
            if (input >= '0' && input <= '9')
            {
                added = 1;
                if (decimalIndex > 0)
                {
                    num = num + ((double)input - '0') / pow(10, decimalIndex);
                    decimalIndex++;
                }
                else num = num * 10 + (input - '0'); // Regular number
            }
            else if (input == '-' && added == 0)
                negative = 1;
            else if (input == '.')
                decimalIndex = 1;
            else if (input == '\n' && added == 1)
                endCheck = 1;
            else
                invalid = 1;
        }

        if (invalid == 1)
            printf("[ERROR] Invalid input ! Please enter again: ");

        rewind(stdin);
    } while(invalid == 1);
    if (negative == 1)
        num *= -1.0;
    return num;
}

double diff(double x, double a, double b, double c)
{
    double ans = (a*x*x + b*x +c)/(2.0*a*x+b);
    return ans;
}

double Newton_Raphson (double a, double b, double c, double *Xn)
{
    double Xp, delta;
    int times = 1;
    Xp = -100;
    do
    {
        if (2.0*a*Xp+b == 0)
            Xp += 0.0000001;
        delta = diff( Xp, a, b, c);
        *Xn = Xp - delta;
        Xp = *Xn;
        times++;
        printf("\n === %d \n", delta);
    } while(fabs(delta) > 0.00001);
    if (times < 100000)
        return times;
    else return 0;
}
