#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int load_txt_file (char *filename, int data[], int *count)
{
    FILE *file;
    int a;
    if ((file = fopen(filename, "r")) != NULL)
    {
        *count = 0;
        while (fscanf(file, "%d", &a) == 1)
        {
            data[*count] = a;
            *count = *count + 1;
        }
        fclose(file);

    } else {
        printf("Can't read file.");
    }
    return 0;
}

void load_binary_file (char *filename, int data[], int *count)
{
    FILE *file;
    int a;
    if ((file = fopen(filename, "rb")) != NULL)
    {
        *count = 0;
        while (!feof(file))
        {
            if (fread(&a, sizeof(int), 1, file ) == 1)
            {
                data[*count] = a;
                *count = *count + 1;
            }
        }
        fclose(file);
    } else {
        printf ("Can't read file");
    }

}

void preview (int data[], int *count)
{
    int i;
    for (i = 0; i < *count; i++)
        printf("%d\n", data[i]);
}

int comparator(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b);
}


void sol1 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{
    clock_t startTime, endTime;
    double totalTime;
    printf("\n\n ============ Case 1 ============\n");
    startTime = clock();

    int i, j;
    for (i = 0; i < *count1;i++) { // data 1
        for (j = 0; j < *count2; j++) { // data 2
            if (data1[i] == data2[j]) // Found same data
            {
                printf("Found: %d \n", data1[i]);
                result[*resultCount] = data1[i];
                *resultCount = *resultCount + 1;
            }
        }
    }
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}

void sol2 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{
    clock_t startTime, endTime;
    double totalTime;
    printf("\n\n ============ Case 2 ============\n");
    startTime = clock();

    int i, j;
    qsort(data2, *count2, sizeof(int), comparator); // Sort data2
    for (i = 0; i < *count1;i++) { // data 1
        // Binary search
        if ((int*)bsearch(&data1[i], data2, *count2, sizeof(int), comparator) != NULL)  {
            printf("Found: %d \n", data1[i]);
            result[*resultCount] = data1[i];
            *resultCount = *resultCount + 1;
        }
    }
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}
void sol3 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{
    clock_t startTime, endTime;
    double totalTime;
    printf("\n\n ============ Case 3 ============\n");
    startTime = clock();

    int i, j;
    qsort(data1, *count1, sizeof(int), comparator); // Sort data 2
    qsort(data2, *count2, sizeof(int), comparator); // Sort data 2
    for (i = 0, j = 0; i < *count1;) { // data 1
        if (data1[i] < data2[j]) {
            i++; // Go to check next data 1
        } else if (data1[i] > data2[j]) {
            j++; // Go to check next data 2
        } else { // data1 == data2
            printf("Found: %d \n", data1[i]);
            result[*resultCount] = data1[i];
            *resultCount = *resultCount + 1;
            i++; // Go to next data 1
            j++; // Go to next data 2
        }
    }
    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}

void reset(int result[], int *resultCount) {

}

int main ()
{
    int txt[100000], binary[100000], result[100000];
    int txtCount = 0, binaryCount = 0, resultCount = 0;
    double time1 = 0, time2 = 0, time3 = 0;
    load_txt_file("txt100000.txt", txt, &txtCount);
    printf("Txt Count: %d\n", txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    printf("Binary Count: %d\n", binaryCount);

    sol1(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time1);
    resultCount = 0;
    load_txt_file("txt100000.txt", txt, &txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    sol2(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time2);
    resultCount = 0;
    load_txt_file("txt100000.txt", txt, &txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    sol3(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time3);

    printf("\n\n\n=========== RESULT ===========\n");
    printf("Time | Case 1: %f s, Case 2: %f s, Case 3: %f s\n", time1, time2, time3);
    if (time1 < time2 && time1 < time3)
        printf("Case 1 is fastest!!!\n");
    else if (time2 < time1 && time2 < time3)
        printf("Case 2 is fastest!!!\n");
    else if (time3 < time1 && time3 < time2)
        printf("Case 3 is fastest!!!\n");
    else if (time3 == time2)
        printf("Case 3 == Case 2 case.\n");

    return 0;
}
