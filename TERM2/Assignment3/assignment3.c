#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct data_struct {
    long long field1;
    char field2[100];
    char field3[100];
} data_struct;

data_struct data[100000];
data_struct sorting_data[100000];
int count;

void read_file (char *filename, int * count)
{
    printf("Loading file.");
    FILE *file;
    int a;
    *count = 0;
    if ((file = fopen(filename, "r")) != NULL)
    {
        data_struct tmp;
        char newline;

        while (fscanf(file, "%llu,%[^,],%s", &tmp.field1, &tmp.field2, &tmp.field3) == 3)
        {
            data[*count] = tmp;
            *count = *count + 1;
        }
        printf("\n Count: %d", *count);
        fclose(file);
        printf("\n  File readed.");
    } else {
        printf("Can't read file.");
    }
}

int cmp_field1 (const void * a, const void * b)
{
    data_struct * d1 = (data_struct *)a;
    data_struct * d2 = (data_struct *)b;
    if (d1->field1 < d2->field1) return -1;
    else if (d1->field1 > d2->field1) return 1;
    else return 0;
}

int cmp_field3 (const void * a, const void * b)
{
    return strcmp((*(data_struct *)a).field3, (*(data_struct *)b).field3);
}

void print_index_data (data_struct data[], int index)
{
    printf("\n data[%d] = %llu, %s, %s", index, data[index].field1, data[index].field2, data[index].field3);
}

void print_data (int _count)
{
    int i;
    for (i = 0; i < _count; i++)
    {
        printf("\n data[%d] = %llu, %s, %s", i, data[i].field1, data[i].field2, data[i].field3);
    }
}

void swap (data_struct * a, data_struct * b)
{
    struct data_struct temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort_f1 (data_struct _data[], int first, int last)
{
    int i = first, j = last;
    if (i < j)
    {
        do
        {
            while (_data[i].field1 <= _data[j].field1 && (i < j)) j--;
                if (_data[i].field1 > _data[j].field1) {
                    swap(&_data[i++], &_data[j]);
                }
            while (_data[i].field1 <= _data[j].field1 && (i < j)) i++;
                if (_data[i].field1 > _data[j].field1) {
                    swap(&_data[i], &_data[j--]);
                }
        }
        while(i<j);

        if (first < j - 1) quick_sort_f1(_data, first, j - 1);
        if (i+1 < last) quick_sort_f1(_data, i + 1, last);
    }
}

void quick_sort_f3 (data_struct _data[], int first, int last)
{
    int i = first, j = last;
    if (i < j)
    {
        do
        {
            while (strcmp(_data[i].field3, _data[j].field3) <= 0 && (i < j)) j--;
                if (strcmp(_data[i].field3, _data[j].field3) > 0) {
                    swap(&_data[i++], &_data[j]);
                }
            while (strcmp(_data[i].field3, _data[j].field3) <= 0 && (i < j)) i++;
                if (strcmp(_data[i].field3, _data[j].field3) > 0 ) {
                    swap(&_data[i], &_data[j--]);
                }
        }
        while(i<j);

        if (first < j - 1) quick_sort_f3(_data, first, j - 1);
        if (i+1 < last) quick_sort_f3(_data, i + 1, last);
    }
}

void copy_array (data_struct a[], data_struct b[], int count)
{

    int i = 0;
    for (i = 0; i < count;i++) {
        b[i] = a[i];
    }
}

double my_sort_field1 (int round, data_struct original_data[])
{
    copy_array(original_data, sorting_data, count);

    printf("\n\n=======================================");
    printf("\nMy Sort number : %d", round);
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    quick_sort_f1(sorting_data, 0, count - 1);

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;


    print_index_data(sorting_data, 0);
    print_index_data(sorting_data, 49999);
    print_index_data(sorting_data, 99999);
    printf("\nTime: %f s", totalTime);
    printf("\n=======================================\n");

    return totalTime;
}

double my_sort_field3 (int round, data_struct original_data[])
{
    copy_array(original_data, sorting_data, count);
    printf("\n\n=======================================");
    printf("\nMy Sort string : %d", round);
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    quick_sort_f3(sorting_data, 0, count - 1);

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    print_index_data(sorting_data, 0);
    print_index_data(sorting_data, 49999);
    print_index_data(sorting_data, 99999);
    printf("\nTime: %f s", totalTime);
    printf("\n=======================================\n");

    return totalTime;
}

double qsort_field1 (int round, data_struct original_data[])
{
    copy_array(original_data, sorting_data, count);
    printf("\n\n=======================================");
    printf("\nqort number : %d", round);
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    qsort(sorting_data, count, sizeof(data_struct), cmp_field1);

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    print_index_data(sorting_data, 0);
    print_index_data(sorting_data, 49999);
    print_index_data(sorting_data, 99999);
    printf("\nTime: %f s", totalTime);
    printf("\n=======================================\n");

    return totalTime;
}

double qsort_field3 (int round, data_struct original_data[])
{
    copy_array(original_data, sorting_data, count);
    printf("\n\n=======================================");
    printf("\nqort string : %d", round);
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    qsort(sorting_data, count, sizeof(data_struct), cmp_field3);

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    print_index_data(sorting_data, 0);
    print_index_data(sorting_data, 49999);
    print_index_data(sorting_data, 99999);
    printf("\nTime: %f s", totalTime);
    printf("\n=======================================\n");

    return totalTime;
}

int main ()
{

    read_file("test.csv", &count);

    double myTimeNumber[3], myTimeString[3],qsortTimeNumber[3], qsortTimeString[3], myBestNum, myBestStr, bestNum, bestStr;
    int mycount_num = 0, mycount_str = 0, count_num = 0, count_str = 0;

    myTimeNumber[mycount_num++] = my_sort_field1(mycount_num, data);
    myTimeNumber[mycount_num++] = my_sort_field1(mycount_num, data);
    myTimeNumber[mycount_num++] = my_sort_field1(mycount_num, data);

    qsortTimeNumber[count_num++] = qsort_field1(count_num, data);
    qsortTimeNumber[count_num++] = qsort_field1(count_num, data);
    qsortTimeNumber[count_num++] = qsort_field1(count_num, data);

    myTimeString[mycount_str++] = my_sort_field3(mycount_str, data);
    myTimeString[mycount_str++] = my_sort_field3(mycount_str, data);
    myTimeString[mycount_str++] = my_sort_field3(mycount_str, data);


    qsortTimeString[count_str++] = qsort_field3(count_str, data);
    qsortTimeString[count_str++] = qsort_field3(count_str, data);
    qsortTimeString[count_str++] = qsort_field3(count_str, data);

    int i;
    myBestNum = myTimeNumber[0];
    for (i = 0; i < mycount_num; i++) {
        if (myBestNum > myTimeNumber[i])
            myBestNum = myTimeNumber[i];
    }
    myBestStr = myTimeString[0];
    for (i = 0; i < mycount_str; i++) {
        if (myBestStr > myTimeString[i])
            myBestStr = myTimeString[i];
    }

    bestNum = qsortTimeNumber[0];
    for (i = 0; i < bestNum; i++) {
        if (bestNum > qsortTimeNumber[i])
            bestNum = qsortTimeNumber[i];
    }

    bestStr = qsortTimeString[0];
    for (i = 0; i < bestStr; i++) {
        if (bestStr > qsortTimeString[i])
            bestStr = qsortTimeString[i];
    }

    printf("\n\n\n===================== Result =========================");
    if (myBestNum < bestNum)
        printf("\n  Number sorting: My Sort time < qsort time (%f s < %f s)", myBestNum, bestNum);
    else if (myBestNum > bestNum)
        printf("\n  Number sorting: My Sort time > qsort time (%f s > %f s)", myBestNum, bestNum);

    if (myBestStr < bestStr)
        printf("\n  String sorting: My Sort time < qsort time (%f s < %f s)", myBestStr, bestStr);
    else if (myBestStr > bestStr)
        printf("\n  String sorting: My Sort time > qsort time (%f s > %f s)", myBestStr, bestStr);

    printf("\n\n");

    return 1;
}
