#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstdio>

typedef struct studentData {
    long long id;
    char name[40];
    double mid, fin, atten, total, gpoint = 0, point = 0;
    char grade[3] = "";
};

typedef struct statScoreData {
    double min, max, mean, sd, sum, sumsqrt;
};

studentData student[100];
statScoreData totalStat;
statScoreData midStat;
statScoreData finalStat;
statScoreData attenStat;

int studentCount = 0, aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount, gpa;

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

void read_file (char *filename, int *count)
{
    FILE *file;
    int a;
    if ((file = fopen(filename, "r")) != NULL)
    {
        *count = 0;
        studentData st;
        char newline;
        while (fscanf(file, "%llu ,%[^,] ,%lf ,%lf ,%lf", &st.id, &st.name, &st.mid, &st.fin, &st.atten) == 5)
        {
            st.total = st.mid + st.fin + st.atten;
            student[*count] = st;
            *count = *count + 1;
        }
        fclose(file);
        printf("Student count: %d", studentCount);
    } else {
        printf("Can't read file.");
    }
}

void calculate_grade (studentData data[], int count, int a, int bplus, int b, int cplus, int c, int dplus, int d)
{
    aCount = bplusCount = bCount = cplusCount = cCount = dplusCount = dCount = fCount = 0;
    for (int i = 0; i < count;i++) {
        if (data[i].total >= a) {
            strcpy(data[i].grade, "A");
            data[i].gpoint = 4;
            aCount++;
        } else if (data[i].total >= bplus) {
            strcpy(data[i].grade, "B+");
            data[i].gpoint = 3.5;
            bplusCount++;
        } else if (data[i].total >= b) {
            strcpy(data[i].grade, "B");
            data[i].gpoint = 3.0;
            bCount++;
        } else if (data[i].total >= cplus) {
            strcpy(data[i].grade, "C+");
            data[i].gpoint = 2.5;
            cplusCount++;
        } else if (data[i].total >= c) {
            strcpy(data[i].grade, "C");
            data[i].gpoint = 2.0;
            cCount++;
        } else if (data[i].total >= dplus) {
            strcpy(data[i].grade, "D+");
            data[i].gpoint = 1.5;
            dplusCount++;
        } else if (data[i].total >= d) {
            strcpy(data[i].grade, "D");
            data[i].gpoint = 1.0;
            dCount++;
        } else {
            strcpy(data[i].grade, "F");
            data[i].gpoint = 0.0;
            fCount++;
        }
    }
}

void calculate_statistic (studentData data[], int *count, double *min, double *max, double *mean, double *sd, int type = 0)
{
    double sum = 0, sumsqr = 0, base;
    if (type == 0) base = data[0].total;
    if (type == 1) base = data[0].mid;
    if (type == 2) base = data[0].fin;
    if (type == 3) base = data[0].atten;
    *min = *max = base;
    for (int i = 0; i < *count;i++) {
        double score = 0;
        if (type == 0) score = data[i].total;
        else if (type == 1) score = data[i].mid;
        else if (type == 2) score = data[i].fin;
        else if (type == 3) score = data[i].atten;
        //
        if (*min > score)
            *min = score;
        if (*max < score)
            *max = score;
        sum =  sum + score;
        sumsqr = sumsqr + pow(score, 2);
    }

    *mean = (double)sum/(double)*count;
    *sd = sqrt(sumsqr/ *count - pow(*mean, 2));
}


void showStatistic ()
{
    calculate_statistic(student, &studentCount, &totalStat.min, &totalStat.max, &totalStat.mean, &totalStat.sd);
    calculate_statistic(student, &studentCount, &midStat.min, &midStat.max, &midStat.mean, &midStat.sd, 1);
    calculate_statistic(student, &studentCount, &finalStat.min, &finalStat.max, &finalStat.mean, &finalStat.sd, 2);
    calculate_statistic(student, &studentCount, &attenStat.min, &attenStat.max, &attenStat.mean, &attenStat.sd, 2);

    printf("|   Score   |    mid    |    final   |    atten   |    total   |\n");
    printf("|-----------|-----------|------------|------------|------------|\n");
    printf("|   min     |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", midStat.min, finalStat.min, attenStat.min, totalStat.min);
    printf("|   max     |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", finalStat.max, finalStat.max, attenStat.max, totalStat.max);
    printf("|   mean    |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", finalStat.mean, finalStat.mean, attenStat.mean, totalStat.mean);
    printf("|   sd      |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", finalStat.sd, finalStat.sd, attenStat.sd, totalStat.sd);

    printf("\n");
    printf("|           |   A |  B+ |   B |  C+ |   C |  D+ |  D  |  F  |\n");
    printf("|   score   |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |\n", aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount);

}

void printData (studentData data) {
    printf("%llu | %-40s | %6.2lf | %6.2lf | %6.2lf | %6.2lf |  %-2s | %.1lf |\n",
           data.id, data.name, data.mid, data.fin, data.atten, data.total, data.grade, data.gpoint);
}


void displayList (studentData data[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printData(data[i]);
    }
}

void Sort_by_score (studentData data[], int count)
{
    for (int i = 0; i < count;i++) {
        studentData temp;
        for (int j = i+1; j < count; j++) {
            if (data[i].total < data[j].total) {
                temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }
}

void Sort_by_id (studentData data[], int count)
{
    for (int i = 0; i < count;i++) {
        studentData temp;
        for (int j = i+1; j < count; j++) {
            if (data[i].id > data[j].id) {
                temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }

}

void Search_by_score (studentData data[], int count)
{
    char again;
    double minRange, maxRange;
    do
    {
        printf("Enter min and max score: ");
        scanf("%lf %lf", &minRange, &maxRange);
        int countData = 0;
        for (int i = 0; i < count;i++) {
            if (data[i].total >= minRange && data[i].total <= maxRange) {
                countData++;
                printData(data[i]);
            }
        }
        printf("Count: %d", countData);
        printf("Do you want to search again ? : ");
        scanf("%c", &again);
    }while(again == 'y');
}

void Search_by_score (studentData data[], int count)
{

}

int menu ()
{
    printf("*            [1] Read file                          *\n");
    printf("*            [2] Calculate grade                          *\n");
    printf("*            [3] Statistic                          *\n");
    printf("*            [4] List                          *\n");
    printf("*            [5] List sort by grade                          *\n");
    printf("*            [6] List sort by id                          *\n");
    printf("*            [7] Test 5                          *\n");
    printf("*            [8] Test 5                          *\n");
    printf("*            [9] Test 5                          *\n");
    printf("*                                                *\n");
    printf("*            [0] Exit                            *\n");
    printf("**************************************************\n");
    printf("Select: ");

    return getint(0, 9);
}

void display (int menu)
{
    system("cls");
    if (menu == 1) {
        read_file("score.csv", &studentCount);
    } else if (menu == 2) {
        printf("Enter grade score: A, B+, B, C+, C, D+, D: ");
        int a, bplus, b, cplus, c, dplus, d;
        scanf("%d,%d,%d,%d,%d,%d,%d: ", &a, &bplus, &b, &cplus, &c, &dplus, &d);
        calculate_grade(student, studentCount, a, bplus, b, cplus, c, dplus, d);
        showStatistic();
    } else if (menu == 3) {
        showStatistic();
    } else if (menu == 4) {
        Sort_by_id(student, studentCount);
        displayList(student, studentCount);
    } else if (menu == 5) {
        Sort_by_score(student, studentCount);
        displayList(student, studentCount);
    } else if (menu == 6) {
        Search_by_score(student, studentCount);
    }

}

int main ()
{
    char again;
    int select;
    do {
        rewind(stdin);
        system("cls");
        select = menu();
        display(select);

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
