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
    printHeader("\nArray Statistic\n Program by Nitipoom Unrrom\n v1.0\n");
    printf("*            [1] Add data                        *\n");
    printf("*            [2] Remove data                     *\n");
    printf("*            [3] Statistic                       *\n");
    printf("*            [4] Show array data                 *\n");
    printf("*                                                *\n");
    printf("*            [0] Exit                            *\n");
    printf("**************************************************\n");
    printf("Select: ");

    return get_input(0, 5);
}

double get_double (double min, double max, double *x)
{
    while(scanf("%lf", x) >= 1 && *x >= min && *x <= max )
    {
        return 1;
    }
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
    printHeader("Array Data");
    if (*count > 0) {
        printf("*     Index    *               Value             *\n");
        printf("**************************************************\n");
        for (int i = 0; i <= (*count - 1); i++)
        {

            //printf(" %g", data[i]);
            //printf("*            [1] Add data                        *\n");
            printf("*      %2d      *                     %6g      *\n", i, data[i]);
        }
        printf("**************************************************\n");
        printf("Count: %d", *count);
    } else {
        printf("Currently no data.");
    }
}


void add_data (double *data, int *count)
{
    system("cls");
    double x = -1;
    printHeader("Add data");
    printf("Enter data: ");
    while(get_double(0, 100, &x) == 1 && x > -1 && *count < maxCount)
    {
        //printf("Add %g to Data[%d]\n", x, *count);
        data[*count] = x;
        *count += 1;
        print_data(data, count);
    }
    print_data(data, count);
    if (*count == maxCount)
        printf("Array is max\n");
}

void remove_data (double *data, int *count)
{
    system("cls");
    printHeader("Remove data \n");
    if (*count > 0)
    {

        double x = -1;
        printf("Enter data: ");
        while(get_double(0, 100, &x) == 1 && x > -1)
        {
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
            }
            print_data(data, count);
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
