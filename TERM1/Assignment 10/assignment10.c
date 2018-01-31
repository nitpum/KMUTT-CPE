#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ฟังก์ชันโหลด text ไฟล์และเก็บข้อมูลใส่ array
int load_txt_file (char *filename, int data[], int *count)
{
    FILE *file;
    int a;
    // เปิดไฟล์และตรวจสอบว่าเปิดได้
    if ((file = fopen(filename, "r")) != NULL)
    {
        *count = 0; // รีเซตจำนวน
        // ลูปเก็บเช็คค่าแต่ละบรรทัด
        while (fscanf(file, "%d", &a) == 1)
        {
            // เมื่อเจอค่าเก็บเข้าอาเรย์และนับจำนวนเพิ่ม
            data[*count] = a;
            *count = *count + 1;
        }
        fclose(file);

    } else { // แสดงข้อความเปิดไฟล์ไม่ได้
        printf("Can't read file.");
    }
    return 0;
}

// โหลดข้อมูลไบนารี่จากไฟล์เก็บใส่อาเรย์
void load_binary_file (char *filename, int data[], int *count)
{
    int a;
    FILE *file;
    // เปิดไฟล์และตรวจสอบการเปิด
    if ((file = fopen(filename, "rb")) != NULL)
    {
        *count = 0;
        // ลูปจนกว่าจะจบไฟล์
        while (!feof(file))
        {
            // อ่านบล็อกด้วยขนาดของ int
            if (fread(&a, sizeof(int), 1, file ) == 1)
            {
                // นำค่าที่อ่านได้เก็บเข้าอาเรย์ และนับจำนวนเพิ่ม
                data[*count] = a;
                *count = *count + 1;
            }
        }
        fclose(file);
    } else { // แสดงข้อความเปิดไฟล์ไม่ได้
        printf ("Can't read file");
    }

}

// ฟังก์ชั่นแสดงข้อความทั้งในอาเรย์
void preview (int data[], int *count)
{
    int i;
    for (i = 0; i < *count; i++) // ลูปปริ้นแสดงข้อความทีละตัว
        printf("%d\n", data[i]);
}

// ฟังก์ชันเปรียบเทียบสำหรับใช้ในการเรียง
int comparator(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b);
}

// Solution 1 function
void sol1 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{

    printf("\n\n ============ Case 1 ============\n");

    // เริ่มจับเวลาการทำงาน
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    int i, j;
    for (i = 0; i < *count1;i++) { // ลูปข้อมูล data 1
        for (j = 0; j < *count2; j++) { // ลูปข้อมูล data 2
            if (data1[i] == data2[j]) // เปรียบเทียบข้อมูลหาข้อมูลที่ตรงกัน
            {
                // เมื่อเจอข้อมูลที่ตรงกันแสดงผลและเก็บข้อมูลลงอาเรย์ใหม่
                // นับจำนวนเพิ่ม
                printf("Found: %d \n", data1[i]);
                result[*resultCount] = data1[i];
                *resultCount = *resultCount + 1;
            }
        }
    }
    // หยุดจับเวลา
    endTime = clock();
    // คำนวณเวลาทั้งหมด
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;

    // แสดงผลการจับเวลา
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}

// Solution 2 function
void sol2 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{
    printf("\n\n ============ Case 2 ============\n");

    // เริ่มจับเวลาการทำงาน
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    int i, j;
    qsort(data2, *count2, sizeof(int), comparator); // ใช้ Quick Sort กับ data 2 เรียงจากน้อยไปมาก
    for (i = 0; i < *count1;i++) { // ลูปข้อมูล data 1
        // ใช้ binary search หาข้อมูล data 2 ใน data 1
        if ((int*)bsearch(&data1[i], data2, *count2, sizeof(int), comparator) != NULL)  {
            // เมื่อเจอข้อมูลที่ตรงกันแสดงผลและเก็บข้อมูลลงอาเรย์ใหม่
            // นับจำนวนเพิ่ม
            printf("Found: %d \n", data1[i]);
            result[*resultCount] = data1[i];
            *resultCount = *resultCount + 1;
        }
    }
    // หยุดจับเวลา
    endTime = clock();
    // คำนวณเวลาที่ใช้
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;

    // แสดงผลการจับเวลา
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}

// Solution 3 function
void sol3 (int data1[], int data2[], int result[], int *count1, int *count2, int *resultCount, double *time)
{
    printf("\n\n ============ Case 3 ============\n");

    // เริ่มจับเวลา
    clock_t startTime, endTime;
    double totalTime;
    startTime = clock();

    int i, j;
    qsort(data1, *count1, sizeof(int), comparator); // ใช้ Quick Sort กับ data 1 เรียงจากน้อยไปมาก
    qsort(data2, *count2, sizeof(int), comparator); // ใช้ Quick Sort กับ data 2 เรียงจากน้อยไปมาก
    for (i = 0, j = 0; i < *count1;) { // ลูปข้อมูล data 1
        // เปรียบเทียบค่าระหว่าง data1 กับ data 2
        if (data1[i] < data2[j]) {
            i++; // ค่า 1 ตัวปัจจุบันน้อยกว่าเลื่อนไปดูตัวถัดไป
        } else if (data1[i] > data2[j]) {
            j++; // ค่า 2 ตัวปจจุบันน้อยกว่าเลื่อนไปดูตัวถัดไป
        } else { // ทั้งสองค่าเท่ากัน
            // เมื่อเจอข้อมูลที่ตรงกันแสดงผลและเก็บข้อมูลลงอาเรย์ใหม่
            // นับจำนวนเพิ่ม
            printf("Found: %d \n", data1[i]);
            result[*resultCount] = data1[i];
            *resultCount = *resultCount + 1;
            // เลื่อนไปดูตัวถัดไปทั้งคู่
            i++;
            j++;
        }
    }
    // หยุดจับเวลา
    endTime = clock();
    // คำนวณเวลาทั้งหมด
    totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    *time = totalTime;

    // แสดงผลการจับเวลา
    printf("  Total time: %f s", totalTime);
    printf("\n  Result Count: %d\n", *resultCount);
    preview(result, resultCount);

}

int main ()
{
    // อาเรย์สำหรับเก็บข้อมูล
    int txt[173074], binary[173074], result[173074];
    // จำนวนอาเรย์
    int txtCount = 0, binaryCount = 0, resultCount = 0;
    // เวลา
    double time1 = 0, time2 = 0, time3 = 0;

    // โหลดทั้ง text ไฟล์ และไบนารี่ไฟล์
    load_txt_file("txt100000.txt", txt, &txtCount);
    printf("Txt Count: %d\n", txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    printf("Binary Count: %d\n", binaryCount);

    // รันวิธีที่ 1
    sol1(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time1);

    // รีเซ็ตจำนวนผลลัพธ์
    resultCount = 0;
    // โหลดทั้ง text ไฟล์ และไบนารี่ไฟล์
    load_txt_file("txt100000.txt", txt, &txtCount);
    printf("Txt Count: %d\n", txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    printf("Binary Count: %d\n", binaryCount);
    // รันวิธีที่ 2
    sol2(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time2);

    // รีเซ็ตจำนวนผลลัพธ์
    resultCount = 0;
    // โหลดทั้ง text ไฟล์ และไบนารี่ไฟล์
    load_txt_file("txt100000.txt", txt, &txtCount);
    printf("Txt Count: %d\n", txtCount);
    load_binary_file("bin100000.bin", binary, &binaryCount);
    printf("Binary Count: %d\n", binaryCount);
    // รันวิธีที่ 3
    sol3(txt, binary, result, &txtCount, &binaryCount, &resultCount, &time3);

    // เแสดงเวลาที่ใช้และปรียบเทียบเวลาทั้งสามวิธี จากนั้นแสดงวิธีที่เร็วที่สุด
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
