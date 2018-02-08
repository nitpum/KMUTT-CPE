#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data_struct {
    long long field1;
    char field2[100];
    char field3[100];
    struct data_struct * next;
} linkedlist;
int count;

linkedlist * first = NULL, * last = NULL;

void add_linkedlist (long long f1, char f2[], char f3[])
{
    linkedlist * ptr;
    ptr = (linkedlist *) malloc(sizeof(linkedlist));
    ptr->next = NULL;
    ptr->field1 = f1;
    strcpy(ptr->field2, f2);
    strcpy(ptr->field3, f3);
    if (first == NULL)
        first = last = ptr;
    else { last->next = ptr;
        last = ptr;
    }
    count++;
}

void read_file (char *filename, int * count)
{
    printf("Loading file.");
    FILE *file;
    int a;
    *count = 0;
    // อ่านไฟล์
    if ((file = fopen(filename, "r")) != NULL)
    {
        linkedlist data;
        char newline;
        // อ่านข้อมูลในหนึ่งบรรทัดตาม pattern ที่กำหนดไว้และนำค่าที่ได้เก็บเป็นข้อมูลนักเรียน
        while (fscanf(file, "%llu,%[^,],%s", &data.field1, &data.field2, &data.field3) == 3)
        {
            add_linkedlist(data.field1, data.field2, data.field3);
        }
        fclose(file);
        printf("\n  File readed.");
        //printf("Student count: %d", studentCount); // แสดงจำนวนนักเรียน
    } else {
        printf("Can't read file.");
    }
}

int cmp_field1 (const void * a, const void * b)
{
   return ( *(linkedlist*)a->field1 - *(linkedlist*)b->field1 );
}

int main ()
{
    read_file("test.csv", &count);

    qsort(data, count, sizeof(data_struct), cmp_field1());



    return 1;
}
