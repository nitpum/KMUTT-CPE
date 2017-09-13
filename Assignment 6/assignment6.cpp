#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <string.h>

int menu();
void printHeader(char text[]);
int getIntInput(int minI, int maxI);
void test1(int n);
void test2(int n);
void test3(int n);
void test4(int minNum, int maxNum);
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
            test4(100, 200);
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
    printf("*            [1] 1                               *\n");
    printf("*            [2] 2                               *\n");
    printf("*            [3] 3                               *\n");
    printf("*            [4] 4                               *\n");
    printf("*            [5] 5                               *\n");
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
    for (int i = 1; i <= n; i++)
    {
        result += i * d;
    }
    return result;
}

int countDigit(int digit)
{
    int result = 0;
    if (digit == 0)
        return 1;
    while (digit > 0)
    {
        digit /= 10;
        result++;
    }
    return result;
}

void printRow(int i, int j, int k, int spaceI, int spaceJ, int spaceK)
{
    int iLenght = countDigit(i);
    int jLenght = countDigit(j);
    int kLenght = countDigit(k);
    printf("* ");
    for (int s = 1; s <= spaceI - iLenght;s++)
        printf(" ");
    printf("%d * ", i);
    // J
    for (int s = 1; s<= spaceJ - jLenght;s++)
        printf(" ");
    printf("%d * ", j);
    // K
    for (int s = 1; s<= spaceK - kLenght;s++)
        printf(" ");
    printf("%d *\n", k);
}

void printRow(int i, double j, double k, int spaceI, int spaceJ, int spaceK)
{
    int iLenght = countDigit(i);
    int jLenght = countDigit(j);
    int kLenght = countDigit(k);
    printf("* ");
    for (int s = 1; s <= spaceI - iLenght;s++)
        printf(" ");
    printf("%d * ", i);
    // J
    for (int s = 1; s<= spaceJ - jLenght;s++)
        printf(" ");
    printf("%.6f * ", j);
    // K
    for (int s = 1; s<= spaceK - kLenght;s++)
        printf(" ");
    printf("%.6f *\n", k);
}

void printRow(int i, int j, int spaceI, int spaceJ)
{
    int iLenght = countDigit(i);
    int jLenght = countDigit(j);
    printf("* ");
    for (int s = 1; s <= spaceI - iLenght;s++)
        printf(" ");
    printf("%d * ", i);
    // J
    for (int s = 1; s<= spaceJ - jLenght;s++)
        printf(" ");
    printf("%d *\n", j);
}

void printRow(int i, int j, int k)
{
    printRow(i, j, k, 2, 4, 4);
}

void test1 (int n)
{
    printf("******************************\n");
    printf("*  i *    fi     *    sum    *\n");
    printf("******************************\n");
    double sum  = 0;
    for (int i = 1;i <= n;i++)
    {
        double fi = quickSum(1, i, 2.0) / factorial(i);
        sum += fi;
        printRow(i,  fi, sum, 2, 2, 2);
    }
    printf("******************************\n");
    printf("ans = %f \n", sum);
}

void test2 (int n)
{
    printf("************************\n");
    printf("*count*  i   *    fi   *\n");
    printf("************************\n");
    int i = 1;
    int add = 0;
    while (add < n)
    {
        int fi = fibo(i);
        if (fi % 2 == 0)
        {
            printRow(++add, i, fi, 3, 4, 7);
        }
        i++;
    }
    printf("************************\n");
}

void test3 (int a)
{
    printf("*********************\n");
    printf("* no *  fi  *  sum  *\n");
    printf("*********************\n");
    int sum = 0;
    int i = 1;
    while (sum < a)
    {
        int fi  = (1 + ((i - 1) * 2)) * (40 - (2 * (i - 1)));
        sum += fi;
        printRow( i, fi, sum, 2, 4, 5);
        i++;
    }
    printf("*********************\n");
    printf("n = %d, ans = %d\n", --i, sum);
}

void test4 (int minNum, int maxNum)
{
    printf("********************\n");
    printf("* no *   i  *  sum *\n");
    printf("********************\n");
    int n = 1, sum = 0;
    for (int i = minNum; i<=maxNum; i++)
    {
        if (i%9==0)
        {
            sum += i;
            printRow( n++, i, sum);
            //printRow(n++, i, sum);
        }
    }
    printf("********************\n");
    printf("count = %d, ans = %d\n", n, sum);
}

void test5 (int n)
{
    printf("*************\n");
    printf("* no * term *\n");
    printf("*************\n");
    //printf("%d", sum(2, 4, 2));
    int a,b, order = 1;
    for (int i = 0; i < n; i++)
    {
        a = 1 + (i * 3);
        for (int j = 0; j < n; j++)
        {
            b = 1 + (j * 5);
            if (a == b)
            {
                printRow(order, a, 2, 4);
                j = n;
                order++;
            }
        }
    }
    printf("*************\n");
}

