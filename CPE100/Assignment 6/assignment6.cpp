#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <string.h>

int menu();
void printHeader(char text[]);
int getint(int minI, int maxI);
void test1(int n);
void test2(int n);
void test3(int n);
void test4(int a, int b, int c);
void test5(int n);
void printHeader();

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
            test1(10);
        else if (select == 2)
            test2(10);
        else if (select == 3)
            test3(5000);
        else if (select == 4)
            test4(100, 200, 9);
        else if (select == 5)
            test5(100);

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
    return 0;
}

int menu ()
{
    printHeader("\nAssignment 6\n Program by Nitipoom Unrrom\n v1.0\n");
    printf("*            [1] Test 1                          *\n");
    printf("*            [2] Test 2                          *\n");
    printf("*            [3] Test 3                          *\n");
    printf("*            [4] Test 4                          *\n");
    printf("*            [5] Test 5                          *\n");
    printf("*                                                *\n");
    printf("*            [0] Exit                            *\n");
    printf("**************************************************\n");
    printf("Select: ");

    return getint(0, 5);
}

void printHeader(char text[], int length)
{
    int starCount = length; // star
    int amount = strlen(text),
        lineAmount = 1;
    for (int i = 1; i <= length;i++)
        printf("*");
    printf("\n");

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
                if (lineTextAmount <= length - 3)
                    lineTextAmount++;
            }
        }

        int startAt = (length/2) - lineTextAmount/2;
        int textIndex = 0 + fistTextIndex;
        for (int i = 1; i <= length; i++)
        {
            if (i == 1 || i == length - 1)
                printf("*");
            if (i==length)
                printf("\n");
            else if (i < startAt || i > (startAt - 1) + lineTextAmount)
                printf(" ");
            else if (text[textIndex] == '\n') {
                printf(" ");
            }
            else printf("%c", text[textIndex++]);
        }
    }
    for (int i = 1; i <= length;i++)
        printf("*");
    printf("\n");
}

void printHeader(char text[])
{
    printHeader(text, 50);
}

int getint ()
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
                added++;
            }
            else if (input == '\n' && added > 0)
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

int getint (int minInt, int maxInt)
{
    int input = getint();
    while(input < minInt || input > maxInt)
    {
        printf("[ERROR] Please enter number between %i - %i: ", minInt, maxInt);
        input = getint();
    }
    return input;
}

int factorial (int n)
{
    int result = 1;
    for (int i = n; i > 0;i--)
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


int quickSum (int start, int n, int d)
{
    int result = 0;
    for (int i = start; i <= n; i++)
    {
        result += i * d;
    }
    return result;
}

double quickSum(int start, int n, double d)
{
    double result = 0;
    for (int i = start; i <= n; i++)
    {
        result += i * d;
    }
    return result;
}

void test1 (int n)
{
    printHeader("Test1\n", 30);
    printf("*  i *    fi     *    sum    *\n");
    printf("******************************\n");
    double sum  = 0;
    for (int i = 1;i <= n;i++)
    {
        double fi = quickSum(1, i, 2.0) / factorial(i);
        sum += fi;
        printf("* %2d * %9lf * %9lf *\n", i, fi, sum);
    }
    printf("******************************\n");
    printf("ans = %f \n", sum);
}

void test2 (int n)
{
    printHeader("\nTest 2\n", 24);
    printf("*count*  i   *    fi   *\n");
    printf("************************\n");

    int i = 1;
    int add = 0;
    while (add < n)
    {
        int fi = fibo(i);
        if (fi % 2 == 0)
        {
            printf("* %3d * %4d * %7d *\n", ++add, i, fi);
        }
        i++;
    }
    printf("************************\n");
}

void test3 (int a)
{
    printHeader("\nTest 3\n", 21);
    printf("* no *  fi  *  sum  *\n");
    printf("*********************\n");
    int sum = 0;
    int i = 1;
    while (sum < a)
    {
        int fi  = (1 + ((i - 1) * 2)) * (40 - (2 * (i - 1)));
        sum += fi;
        printf("* %2d * %4d * %5d *\n", i, fi, sum);
        i++;
    }
    printf("*********************\n");
    printf("n = %d, ans = %d\n", --i, sum);
}

void test4 (int a, int b, int c)
{
    printHeader("\nTest 4\n", 21);
    printf("* no *   i  *  sum *\n");
    printf("********************\n");
    int n = 1, sum = 0;
    for (int i = a; i<=b; i++)
    {
        if (i%c==0)
        {
            sum += i;
            printf("* %2d * %4d * %4d *\n", n++, i, sum);
        }
    }
    printf("********************\n");
    printf("count = %d, ans = %d\n", (n-1), sum);
}

void test5 (int n)
{
    printHeader("\nTest 5\n", 13);
    printf("* no * term *\n");
    printf("*************\n");

    int a,b, order = 1;
    for (int i = 0; i < n; i++)
    {
        a = 1 + (i * 3);
        for (int j = 0; j < n; j++)
        {
            b = 1 + (j * 5);
            if (a == b)
            {
                printf("* %2d * %4d *\n", order, a);
                j = n;
                order++;
            }
        }
    }
    printf("*************\n");
}

