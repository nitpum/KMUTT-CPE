#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <string.h>

int getIntInput();
int getIntInput(int minInt, int maxInt);
int menu();
int factorial(int fact);
int fibo(int order);
int nCr(int n, int r);
int nPr(int n, int r);
int GCD(int n, int r);
void printHeader(char text[]);

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
            printHeader("\nFactorial calculator\n");
            printf("Enter factorial: ");
            int fact = getIntInput();
            printf("Result: %i", factorial(fact));
        } else if (select == 2)
        {
            printHeader("\nFibonacci calculator\n");
            printf("Enter fibonacci: ");
            int fiboOrder = getIntInput(0, 100);
            printf("Result: %i", fibo(fiboOrder));
        } else if (select == 3)
        {
            printHeader("\nnCr calculator\n");
            int n, r;
            do
            {
                printf("Enter n: ");
                n = getIntInput();
                printf("Enter r: ");
                r = getIntInput();
                if (n < r)
                    printf("[ERROR] Invalid input n must greater than r");
            } while(n < r);
            printf("Result: %i", nCr(n, r));
        }  else if (select == 4)
        {
            printHeader("\nnPr calculator\n");
            int n, r;
            do
            {
                printf("Enter n: ");
                n = getIntInput();
                printf("Enter r: ");
                r = getIntInput();
                if (n < r)
                    printf("[ERROR] Invalid input n must greater than r");
            } while(n < r);
            printf("Result: %i", nPr(n, r));
        } else if (select == 5)
        {
            printHeader("\nGCD calculators\n");
            int n, r;
            printf("Enter n: ");
            n = getIntInput(1,100000);
            printf("Enter r: ");
            r = getIntInput(1,100000);
            printf("Result: %i", GCD(n, r));
        }

        if (select != 0)
        {
            char input;
            do
            {
                printf("\n\nPress [ENTER] to back to menu.");
                input = getchar();
            } while(input != '\n');
        }
    } while(select != 0);
}

int menu ()
{
    printHeader("\nCalculator\n Program by Nitipoom Unrrom\n v1.0\n");
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

void printHeader(char text[])
{
    int starCount = 50; // star
    int amount = strlen(text),
        lineAmount = 1;
    printf("**************************************************\n");

    // Get line amount
    for (int i = 0; i < amount;i++)
    {
        if (text[i] == '\n')
            lineAmount += 1;
    }
    // Start line
    for (int line = 1; line <= lineAmount;line++)
    {
        int currentLine = 1, lineTextAmount = 0, fistTextIndex = 0;
        for (int i = 0; i < amount && currentLine <= line;i++)
        {
            if (text[i] == '\n')
                currentLine++;
            else if (text[i] != '\n' && currentLine == line)
            {
                if (lineTextAmount == 0)
                    fistTextIndex = i;
                if (lineTextAmount <= 47)
                    lineTextAmount++;
            }
        }

        int startAt = 24 - lineTextAmount/2;
        int textIndex = 0 + fistTextIndex;
        for (int i = 1; i <= 50; i++)
        {
            if (i == 1 || i == 49)
                printf("*");
            if (i==50)
                printf("\n");
            else if (i < startAt || i > (startAt - 1) + lineTextAmount)
                printf(" ");
            else if (text[textIndex] == '\n') {
                printf(" ");
            }
            else printf("%c", text[textIndex++]);
        }
    }
    printf("**************************************************\n");
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
    return factorial(n) / (factorial(r) * factorial(n - r));
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
