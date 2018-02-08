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
int count;

void read_file (char *filename, int * count)
{
    printf("Loading file.");
    FILE *file;
    int a;
    *count = 0;
    // อ่านไฟล์
    if ((file = fopen(filename, "r")) != NULL)
    {
        data_struct tmp;
        char newline;
        // อ่านข้อมูลในหนึ่งบรรทัดตาม pattern ที่กำหนดไว้และนำค่าที่ได้เก็บเป็นข้อมูลนักเรียน
        while (fscanf(file, "%llu,%[^,],%s", &tmp.field1, &tmp.field2, &tmp.field3) == 3)
        {
            data[*count] = tmp;
            //printf("\n%llu, %s, %s", data[*count].field1, data[*count].field2, data[*count].field3);
            *count = *count + 1;
        }
        printf("\n Count: %d", *count);
        fclose(file);
        printf("\n  File readed.");
        //printf("Student count: %d", studentCount); // แสดงจำนวนนักเรียน
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

void print_index_data (int index)
{
    printf("\n Index %d = %llu, %s, %s", index, data[index].field1, data[index].field2, data[index].field3);
}

void print_data (int _count)
{
    int i;
    for (i = 0; i < _count; i++)
    {
        printf("\n data[%d] = %llu, %s, %s", i, data[i].field1, data[i].field2, data[i].field3);
    }
}

void swap (int a, int b)
{
    data_struct temp;
    temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}

void quick_sort_f1 (data_struct _data[], int first, int last)
{
    int i = first, j = last;
    if (i < j)
    {
        do
        {
            while (data[i].field1 <= data[j].field1 && (i < j)) j--;
                if (data[i].field1 > data[j].field1) {
                    swap(i++, j);
                }
            while (data[i].field1 <= data[j].field1 && (i < j)) i++;
                if (data[i].field1 > data[j].field1) {
                    swap(i, j--);
                }
        }
        while(i<j);

        if (first < j - 1) quick_sort_f1(data, first, j - 1);
        if (i+1 < last) quick_sort_f1(data, i + 1, last);
    }
}

void quick_sort_f3 (data_struct _data[], int first, int last)
{
    int i = first, j = last;
    if (i < j)
    {
        do
        {
            while (strcmp(data[i].field3, data[j].field3) <= 0 && (i < j)) j--;
                if (strcmp(data[i].field3, data[j].field3) > 0) {
                    swap(i++, j);
                }
            while (strcmp(data[i].field3, data[j].field3) <= 0 && (i < j)) i++;
                if (strcmp(data[i].field3, data[j].field3) > 0 ) {
                    swap(i, j--);
                }
        }
        while(i<j);

        if (first < j - 1) quick_sort_f1(data, first, j - 1);
        if (i+1 < last) quick_sort_f1(data, i + 1, last);
    }
}

int main ()
{
    read_file("test.csv", &count);

    //printf("\n%llu, %llu", data[0].field1, data[count - 1].field1);
    //print_index_data(999999900000);
    //qsort(data, count, sizeof(data_struct), cmp_field1);
    //printf("\n%llu, %llu", data[0].field1, data[2].field1);

    quick_sort_f3(data, 0, count - 1);
    print_data(10);
    //print_index_data(0); print_index_data(count - 1);



    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    endTime = clock();
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("\n");
    //qsort(data, count, sizeof(data_struct), cmp_field3);
    qsort(data, count, sizeof(data_struct), cmp_field3);
    print_data(10);
    //print_index_data(0); print_index_data(count - 1);

    print_index_data(0);
    print_index_data(49999);
    print_index_data(99999);

    return 1;
}
