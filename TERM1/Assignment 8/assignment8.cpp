#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string.h>

const int maxCount = 20;
double data[maxCount];

double get_double(double min, double max, double *x);
int get_input();
int get_input(int min, int max);
void add_data(double *data, int *count);
void remove_data(double *data, int *count);
void statistic(double *data, int *count);
void print_data(double *data, int *count);
void ShowData(double *data, int *count);
int menu();
void printHeader(char text[]);


int main ()
{
    int count = 0;
    int select;
    do
    {
        system("cls");
        printHeader("\nArray Statistic\n Program by Nitipoom Unrrom\n v1.0\n");
        printf("*            [1] Add data                        *\n");
        printf("*            [2] Remove data                     *\n");
        printf("*            [3] Statistic                       *\n");
        printf("*                                                *\n");
        printf("*            [0] Exit                            *\n");
        printf("**************************************************\n");
        ShowData(data, &count);
        printf("\nSelect: ");
        select = menu();

        if (select == 1)
        {
            add_data(data, &count);
        }
        else if (select == 2)
        {
            remove_data(data, &count);
        }
        else if (select == 3)
        {
            system("cls");
            statistic(data, &count);
        }
        else if (select == 4)
        {
            system("cls");
            ShowData(data, &count);
        }
        if (select != 0)
        {
            char input;
            rewind(stdin);
            do
            {
                printf("\n\nPress [ENTER] to back to menu.");
                input = getchar();
            } while(input != '\n');
        }

    } while (select != 0);

    return 0;
}

int menu ()
{
    return get_input(0, 5);
}

int YesOrNo ()
{
    char c = getchar();
    while (c != 'n' && c != 'N' && c != 'Y' && c != 'y')
    {
        printf("Please enter [Y/n] : \n");
        c = getchar();
    }
    if (c == 'Y' || c == 'y')
        return 1;
    else return 0;
}

double get_double (double min, double max, double data[], int *count)
{
    int end = 0;
    double x;
    char c;
    while(*count < 20 && end == 0 && scanf("%lf%c", &x, &c) == 2)
    {
        data[*count] = x;
        *count = *count + 1;
        if (c == '\n') end = 1;
    }
    rewind(stdin);
    return 0;
}

void print_data (double *data, int *count)
{

    //printHeader("Array Data");
    printf("Array {");
    for (int i = 0; i <= (*count - 1); i++)
    {
        //printf("Data[%d]: %g\n", i, data[i]);
        printf(" %g", data[i]);
        if (i < *count - 1)
            printf(",");
    }
    printf(" }\n");
}

void ShowData (double *data, int *count)
{
    if (*count > 0) {
        printf("\n");
        for (int i = 0; i <= (*count - 1); i++)
        {
            printf("   data[%2d] :  %6g      \n", i, data[i]);
        }
        printf("\n                Count: %d\n", *count);
        printf("\n**************************************************\n");
    } else {
        printf("\nCurrently no data.\n");
    }
}

void add_data (double *data, int *count)
{
    system("cls");
    printHeader("Add data");
    printf("Enter data: ");

    double x[maxCount];
    int xCount = 0;
    get_double(0, 100, x, &xCount);
    for (int i = 0; i < xCount;i++)
    {
        data[*count] = x[i];
        *count += 1;
    }
    ShowData(data, count);
    if (*count == maxCount)
        printf("Array is max\n");
}

void remove_data (double *data, int *count)
{
    system("cls");
    printHeader("Remove data \n");
    if (*count > 0)
    {

        double x[maxCount];
        int xCount = 0;
        printf("Enter data: ");
        get_double(0, 100, x, &xCount);
        printf("Data that you want to delete\n ");
        for (int i = 0; i < *count;i++)
        {
            for (int j = 0; j < xCount;j++) {
                if (data[i] == x[j])
                    printf("  data[%d] :  %6g\n", i, data[i]);
            }
        }
        printf("Confirm delete data [Y/n]: ");
        if (YesOrNo() == 1)
        {
            for (int j = 0; j < xCount;j++) {
                for (int i = (*count-1); i >= 0;i--)
                {
                    if (data[i] == x[j])
                    {
                        for (int k = i; i < (*count - 1);k++)
                        {
                            data[k] = data[k+1];
                        }
                        *count = *count-1;
                    }
                }
            }
            /*
            for (int i = (*count - 1); i >= 0; i--)
            {
                int value = x;
                if (data[i] == value)
                {
                    printf("Remove Data[%d] = %d\n", i, value);
                    for (int j = i; j <= (*count - 1);j++)
                    {
                        if (j < (*count - 1))
                            data[j] = data[j + 1];
                    }
                    *count -= 1;
                }
            }*/
        }

        print_data(data, count);
    } else {
        printf("Currently no data.\n");
    }
}

void statistic (double *data, int *count)
{
    printHeader("Statistic");
    if (*count > 1)
    {
        double min = data[0], max = data[0], mean, sd;
        double sum = 0, sum2 = 0;
        for (int i = 0; i < *count;i++)
        {
            sum += data[i];
            sum2 += pow(data[i], 2);
            if (data[i] < min)
                min = data[i];
            if (data[i] > max)
                max = data[i];
        }
        mean = sum / *count;
        sd = sqrt((sum2/ *count) - pow(mean, 2) );
        printf("*          min      :             %6g         *\n", min);
        printf("*          max      :             %6g         *\n", max);
        printf("*          mean     :             %6g         *\n", mean);
        printf("*          sd       :             %6g         *\n", sd);
        printf("**************************************************\n");

    } else if (*count < 2) {
        printf("Data must be at least 2 data.");
    } else {
        printf("Currently no data.\n");
    }
}

int get_input ()
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

int get_input(int min, int max) {
    int input = get_input();
    while(input < min || input > max)
    {
        printf("[ERROR] Please enter number between %i - %i: ", min, max);
        input = get_input();
    }
    return input;
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
