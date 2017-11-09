#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct studentData {
    long long id;
    char name[40];
    double mid, final, atten, total, gpoint;
    char grade[3];
};

typedef struct statScoreData {
    double min, max, mean, sd, sum, sumsqrt;
};

studentData student[100];
statScoreData statMid;
int studentCount = 0, aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount;
double min, max, mean, sd;

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
        while (fscanf(file, "%llu,%[^,],%lf,%lf,%lf", &st.id, &st.name, &st.mid, &st.final, &st.atten) == 5)
        {
            st.total = st.mid + st.final + st.atten;
            student[*count] = st;
            *count = *count + 1;
        }
        fclose(file);
        printf("Student count: %d", studentCount);
    } else {
        printf("Can't read file.");
    }
}

void calculate_grade (studentData data[], int *count, int a, int bplus, int b, int cplus, int c, int dplus, int d)
{
    aCount = bplusCount = bCount = cplusCount = cCount = dplusCount = dCount = fCount;
    for (int i = 0; i < *count;i++) {
        if (data[i].total >= a) {
            strcpy(data[i].grade, "A");
            aCount++;
        } else if (data[i].total >= bplus) {
            strcpy(data[i].grade, "B+");
            bplusCount++;
        } else if (data[i].total >= b) {
            strcpy(data[i].grade, "B");
            bCount++;
        } else if (data[i].total >= cplus) {
            strcpy(data[i].grade, "C+");
            cplusCount++;
        } else if (data[i].total >= c) {
            strcpy(data[i].grade, "c");
            cCount++;
        } else if (data[i].total >= dplus) {
            strcpy(data[i].grade, "D+");
            dplusCount++;
        } else if (data[i].total >= d) {
            strcpy(data[i].grade, "D");
            dCount++;
        } else {
            strcpy(data[i].grade, "F");
            fCount++;
        }
    }
}

void calculate_statistic (studentData data[], int *count, statScoreData *statMid, double *min, double *max, double *mean, double *sd)
{
    double sum, sumsqr;
    *min = *max = data[0].total;
    statMid.min = statMid.max = data[0].mid;
    (*statMid).sum = (*statMid).sumsqrt = 0;
    for (int i = 0; i < studentCount;i++) {

        // Mid
        if ((*statMid).min > data[i].mid)
            (*statMid).min = data[i].mid;
        if ((*statMid).max < data[i].mid)
            (*statMid).max = data[i].mid;
        (*statMid).sum = (*statMid).sum + data[i].mid;
        (*statMid).sumsqrt = (*statMid).sumsqrt + pow(data[i].mid, 2);

        if (*min > data[i].total)
            *min = data[i].total;
        if (*max < data[i].total)
            *max = data[i].total;
        sum += data[i].total;
        sumsqr += pow(data[i].total, 2);
    }
    (*statMid).mean = (*statMid).sum/studentCount;

    *mean = sum/studentCount;
    *sd = sqrt(sumsqr/studentCount - pow(*mean, 2));
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
    if (menu == 1) {
        read_file("score.csv", &studentCount);
    } else if (menu == 2) {
        printf("Grade score: A, B+, B, C+, C, D+, D");
        int a, bplus, b, cplus, c, dplus, d;
        scanf("%d,%d,%d,%d,%d,%d,%d: ", &a, &bplus, &b, &cplus, &c, &dplus, &d);
        calculate_grade(student, &studentCount, a, bplus, b, cplus, c, dplus, d);
        printf("%d, %d, %d, %d, %d, %d, %d, %d", aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount);
    } else if (menu == 3) {

        calculate_statistic(student, &studentCount, &statMid, &min, &max, &mean, &sd);
        printf("%lf, %lf, %lf, %lf", &statMid.min, &statMid.max, &statMid.mean, &statMid.sd);
    }

}

int main ()
{
    char again;
    int select;
    do {
        rewind(stdin);
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
