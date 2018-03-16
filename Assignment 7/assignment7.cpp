#include <stdio.h>
#include <math.h>
#include <cstdlib>

double diff(double x, double a, double b, double c);
double Newton_Raphson (double Xp, double a, double b, double c, double *Xn);
double getdouble ();
double getdouble (double min, double max);
void calculator();

int main ()
{
    char again;
    do
    {
        system("cls");

        calculator();

        printf("\n\n\nDo you want to use again ? [Y/n]: ");
        again = getchar();
        while(again != 'y' && again != 'Y' && again != 'N' && again != 'n')
        {
            rewind(stdin);
            printf("Please enter [Y/n] : ");
            again = getchar();
        }

    } while (again == 'y' || again == 'Y');

    return 0;
}

void calculator ()
{
    int a, b, c, times1, times2;
    double x1, x2;
    printf("====================================\n");
    printf("\nCalculator (ax^2 + bx + c)/ 2ax+b \n");
    printf("====================================\n");
    printf("Enter a: "); a = getdouble();
    printf("Enter b: "); b = getdouble();
    printf("Enter c: "); c = getdouble();
    times1 = Newton_Raphson(100.253, a, b, c, &x1);
    times2 = Newton_Raphson(-100.253, a, b, c, &x2);
    if (times1 == 0 && times2 == 0)
        printf("Error ! Can't find anwser");
    else if (fabs(x1 - x2) < 0.000001) printf("Your anwser is : %g", x1);
    else printf("Your anwser is : %g, %g", x1, x2);
}

double diff(double x, double a, double b, double c)
{
    return (a*x*x + b*x +c)/(2.0*a*x+b);
}

double Newton_Raphson (double Xp, double a, double b, double c, double *Xn)
{
    double delta;
    int limit = 1000, count, addCount;
    do
    {
        addCount = 0;
        while (2.0*a*Xp+b == 0 && addCount <= limit)
        {
            Xp += 0.0000001;
            addCount++;
        }
        delta = diff( Xp, a, b, c);
        *Xn = Xp - delta;
        Xp = *Xn;
        count++;
    } while(fabs(delta) > 0.0000001 && count <= limit && addCount <= limit);
    if (count <= limit && addCount <= limit)
        return count;
    else return 0;
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

double getdouble (double min, double max)
{
    double result = getdouble();
    while(result < min || result > max)
    {
        printf("[ERROR] Please number between %d - %d: ", min, max);
        result = getdouble();
    }
    return result;
}

