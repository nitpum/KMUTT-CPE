#include <stdio.h>
#include <math.h>
#include <cstdlib>

double getDoubleInput();
int getIntInput();
int getIntInput(int minInt, int maxInt);
int menu();
int factorial(int fact);
int fibo(int order);
int nCr(int n, int r);
int nPr(int n, int r);
int GCD(int n, int r);

int main ()
{
    int select;

    do
    {
        system("cls");
        select = menu();
        if (select != 0)
            system("cls");
        if (select == 1)
        {
            printf("Enter factorial: ");
            int fact = getIntInput();
            printf("Result: %i", factorial(fact));
        } else if (select == 2)
        {
            printf("Fibonaci calculator\n");
            printf("Enter fibonaci: ");
            int fiboOrder = getIntInput(0, 100);
            printf("Result: %i", fibo(fiboOrder));
        } else if (select == 3)
        {
            printf("nCr calculator");
            int n, r;
            do
            {
                printf("\nEnter n: ");
                n = getIntInput();
                printf("Enter r: ");
                r = getIntInput();
                if (n < r)
                    printf("[ERROR] Invalid input n must greater than r");
            } while(n < r);
            printf("Result: %i", nCr(n, r));
        }  else if (select == 4)
        {
            printf("nPr calculator");
            int n, r;
            do
            {
                printf("\nEnter n: ");
                n = getIntInput();
                printf("Enter r: ");
                r = getIntInput();
                if (n < r)
                    printf("[ERROR] Invalid input n must greater than r");
            } while(n < r);
            printf("Result: %i", nPr(n, r));
        } else if (select == 5)
        {
            printf("GCD calculator");
            int n, r;
            printf("\nEnter n: ");
            n = getIntInput();
            printf("Enter r: ");
            r = getIntInput();
            printf("Result: %i", GCD(n, r));
        }

        if (select != 0)
        {
            char input;
            do
            {
                printf("\nPress enter to back to menu.");
                input = getchar();
            } while(input != '\n');
        }
    } while(select != 0);
}

int menu ()
{
    printf("**************************************************\n");
    printf("*                      Menu                      *\n");
    printf("**************************************************\n");
    printf("*            [1] Factorial function              *\n");
    printf("*            [2] Fibonacci function              *\n");
    printf("*            [3] nCr function                    *\n");
    printf("*            [4] nPr function                    *\n");
    printf("*            [5] GCD function                    *\n");
    printf("*                                                *\n");
    printf("*            [0] Exit                            *\n");
    printf("**************************************************\n");
    printf("Select: ");

    return getIntInput(0, 5);
}

double getDoubleInput ()
{
    int endCheck, invalid, decimalIndex;
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
    return num;
}

int getIntInput ()
{
    int invalid, num, added, endCheck;
    char input;
    do
    {
        num = 0;
        invalid = 0;
        added = 0;
        endCheck = 0;
        while (endCheck == 0 && invalid == 0)
        {

            input = getchar();
            if (input >= '0' && input <= '9')
            {
                num = num * 10 + (input - '0');
                added = 1;
            }
            else if (input == '\n' && added == 1)
                endCheck = 1;
            else
                invalid = 1;
        }
        if (invalid == 1)
            printf("[ERROR] Invalid input ! Please enter again: ");

        rewind(stdin);

    } while(invalid == 1);
    return num;
}



int getIntInput (int minInt, int maxInt)
{

    int input = getIntInput();
    while(input < minInt || input > maxInt)
    {
        printf("[ERROR] Please enter number between %i - %i: ", minInt, maxInt);
        input = getIntInput();
    }
    return input;
}

int factorial (int fac)
{
    int result = 1;
    for (int i = fac; i > 0;i--)
    {
        result = result * i;
    }
    return result;
}

int fibo (int order)
{
    if (order <= 1)
        return order;
    else
        return fibo(order - 1) + fibo(order - 2);
}

int nCr(int n, int r)
{
    return factorial(n) / (factorial(r) * (factorial(n - r)));
}

int nPr(int n, int r)
{
    return factorial(n) / factorial(n - r);
}

int GCD(int n, int r)
{
    if (n%r==0)
        return r;
    else return GCD(r, n%r);
}
