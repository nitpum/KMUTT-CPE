#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstdio>

// โครงสร้างข้อมูลนักเรียน
typedef struct studentData {
    long long id;
    char name[40];
    double mid, fin, atten, total, gpoint = 0, point = 0;
    char grade[3] = "";
};

// โครงสร้างทางสถิติ
typedef struct statScoreData {
    double min, max, mean, sd, sum, sumsqrt;
};

int file_loaded = 0;
// ข้อมูลนักเรียนและข้อมูลทางสถิติต่างๆ
studentData student[100];
statScoreData totalStat;
statScoreData midStat;
statScoreData finalStat;
statScoreData attenStat;
// ตัวแปรนับจำนวนต่างๆ
int studentCount = 0, aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount;
double gpa;

// ฟังก์ชันรับตัวเลขที่ผู้ใช้พิมพ์มา
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
// ฟังก์ชันรับตัวเลข(int) แบบกำหนดขอบเขตได้
int getint (int minInt, int maxInt)
{
    int input = getint(); // ใช้ฟังก์ชัน getint อันเดิมมารับค่า
    while(input < minInt || input > maxInt) // ตรวจสอบขอบเจต
    {
        printf("[ERROR] Please enter number between %i - %i: ", minInt, maxInt);
        input = getint(); // เกินขอบเขตรับค่าใหม่
    }
    return input; // ค่าไม่เกินส่งต่อ
}

// ฟังก์ชันอ่านไฟล์
void read_file (char *filename, int *count)
{
    FILE *file;
    int a;
    // อ่านไฟล์
    if ((file = fopen(filename, "r")) != NULL) 
    {
        *count = 0;
        studentData st;
        char newline;
        // อ่านข้อมูลในหนึ่งบรรทัดตาม pattern ที่กำหนดไว้และนำค่าที่ได้เก็บเป็นข้อมูลนักเรียน
        while (fscanf(file, "%llu ,%[^,] ,%lf ,%lf ,%lf", &st.id, &st.name, &st.mid, &st.fin, &st.atten) == 5)
        {
            st.total = st.mid + st.fin + st.atten; // นับคะแนนรวม
            student[*count] = st; // เก็บข้อมูลเข้า array
            *count = *count + 1; // นับจำนวนเพิ่ม
        }
        fclose(file);
        printf("Student count: %d", studentCount); // แสดงจำนวนนักเรียน
        file_loaded = 1;
    } else {
        printf("Can't read file.");
        file_loaded = 0;
    }
}

// ฟังก์ชันคำนวณเกรด
void calculate_grade (studentData data[], int count, int a, int bplus, int b, int cplus, int c, int dplus, int d)
{
    // รีเซตจำนวนเกรดทั้งหมดให้เป็น 0
    aCount = bplusCount = bCount = cplusCount = cCount = dplusCount = dCount = fCount = 0;
    // ลูปตรวจสอบข้อมูลทั้งอาเรย์
    for (int i = 0; i < count;i++) {
        // เปรีนยเทียบคะแนนตามเกณของเกรดต่างๆ
        // เมื่อตรงเกณ กำหนดเกรดที่ได้และคะแนน
        // นับจำนวนเกรดเพิ่ม
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

// ฟังก์ชันทางสถิติ
void calculate_statistic (studentData data[], int *count, double *min, double *max, double *mean, double *sd, int type = 0)
{
    double sum = 0, sumsqr = 0, base;
    // ตรวจสอบดูว่าเป็นข้อมูลสถิติชนิดไหน จากนั้นกำหนดค่าเริ่มต้นให้เท่ากับข้อมูลตัวที่หนึ่ง
    if (type == 0) base = data[0].total;
    if (type == 1) base = data[0].mid;
    if (type == 2) base = data[0].fin;
    if (type == 3) base = data[0].atten;
    *min = *max = base; // กำหนด max, min ให้เท่ากับค่าเริ่มต้น
    // ลูปข้อมูล
    for (int i = 0; i < *count;i++) {
        double score = 0;
        // เก็บคะแนน ตามประเภทข้อมู,
        if (type == 0) score = data[i].total;
        else if (type == 1) score = data[i].mid;
        else if (type == 2) score = data[i].fin;
        else if (type == 3) score = data[i].atten;
        // ตรวจสอบคะแนน หากเป็นคะแนนต่ำสุดหรือคะแนนสูงสุดจะเก็บไว้
        if (*min > score)
            *min = score;
        if (*max < score)
            *max = score;
        // บวกผลรวม
        sum =  sum + score; 
        sumsqr = sumsqr + pow(score, 2);
    }

    // หาค่าเฉลี่ยนและ sd
    *mean = (double)sum/(double)*count;
    *sd = sqrt(sumsqr/ *count - pow(*mean, 2));
}

// ฟังก์ชันแสดงผลสถิติทั้งหมด
void showStatistic ()
{
    // คำนวณผลทางสถิติประเถทต่างๆ
    calculate_statistic(student, &studentCount, &totalStat.min, &totalStat.max, &totalStat.mean, &totalStat.sd);
    calculate_statistic(student, &studentCount, &midStat.min, &midStat.max, &midStat.mean, &midStat.sd, 1);
    calculate_statistic(student, &studentCount, &finalStat.min, &finalStat.max, &finalStat.mean, &finalStat.sd, 2);
    calculate_statistic(student, &studentCount, &attenStat.min, &attenStat.max, &attenStat.mean, &attenStat.sd, 3);
    // รีเซตค่า GPA
    gpa = 0.0; 
    // ลูปข้อมูลนักเรียน
    for (int i = 0; i < studentCount; i++) {
        gpa += student[i].gpoint; // เพิ่มคะแนนลงใน GPA
    }
    gpa /= studentCount; // คำนวณค่าเฉลี่ยน

    // แสดงผลสถิติ
    printf("|   Score   |    mid    |    final   |    atten   |    total   |\n");
    printf("|-----------|-----------|------------|------------|------------|\n");
    printf("|   min     |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", midStat.min, finalStat.min, attenStat.min, totalStat.min);
    printf("|   max     |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", midStat.max, finalStat.max, attenStat.max, totalStat.max);
    printf("|   mean    |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", midStat.mean, finalStat.mean, attenStat.mean, totalStat.mean);
    printf("|   sd      |   %6.2lf  |   %6.2lf   |   %6.2lf   |   %6.2lf   |\n", midStat.sd, finalStat.sd, attenStat.sd, totalStat.sd);

    printf("\n");
    printf("|           |   A |  B+ |   B |  C+ |   C |  D+ |  D  |  F  |\n");
    printf("|   score   |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |  %2d |\n", aCount, bplusCount, bCount, cplusCount, cCount, dplusCount, dCount, fCount);

    printf("\nGPA: %.2lf", gpa);

}

// ฟักง์ชันแสดงผลข้อมูลของนักเรียนนึ่งคน
void printData (studentData data) {
    printf("%llu | %-40s | %6.2lf | %6.2lf | %6.2lf | %6.2lf |  %-2s | %.1lf |\n",
           data.id, data.name, data.mid, data.fin, data.atten, data.total, data.grade, data.gpoint);
}

// แสดงผลข้อมูลของนักเรียนในอาเรย์
void DisplayList (studentData data[], int count)
{
    printf("     ID     |                   NAME                   |   MID  |  FINAL |  ATTEN |  TOTAL |GRADE|POINT|\n");
    printf("            |                                          |        |        |        |        |     |     |\n");
    // ลูปข้อมูลนักเรียน
    for (int i = 0; i < count; i++)
    {
        printData(data[i]); // แสดงผลนักเรียนแต่ละคน
    }
    printf("Count: %d", count);
}

// ฟังก์ชันเรียงลำดับข้อมูลล้วยคะแนน เรียงจากมากไปน้อย
void Sort_by_score (studentData data[], int count)
{
    // ลูปดูข้อมูล
    for (int i = 0; i < count;i++) {
        // ลูปดูข้อมูลตัวอื่น
        for (int j = i+1; j < count; j++) {
            // เปรียบเทียบคะแนนกับข้อมูลอื่น
            if (data[i].total < data[j].total) {
                // เมื่อคะแนนข้อมูลอื่นเยอะกว่า จึงสลับตำแหน่งข้อมูล
                studentData temp;
                temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }
}

// เรียงข้อมูลด้วยรหัสนักเรียน เรียงจากน้อยไปมาก
void Sort_by_id (studentData data[], int count)
{
    // ลูปดูข้อมูล
    for (int i = 0; i < count;i++) {
        studentData temp;
        for (int j = i+1; j < count; j++) {
            // เปรียบเทียบคะแนนกับข้อมูลอื่น
            if (data[i].id > data[j].id) {
                // เมื่อรหัสข้อมูลอื่นเยอะกว่า จึงสลับตำแหน่งข้อมูล
                temp = data[j];
                data[j] = data[i];
                data[i] = temp;
            }
        }
    }

}

// ฟังก์ชันค้นหานักเรียนที่มีคะแนนอยู่ในขอบเขคที่กำหนด
void Search_by_score (studentData data[], int count)
{
    char again;
    double minRange, maxRange;
    do
    {
        // รับค่าขอบเขตคะแนน
        rewind(stdin);
        system("cls");
        printf("Enter min and max score: ");
        scanf("%lf %lf", &minRange, &maxRange);
        int countData = 0;
        // ลูปค้นหานักเรียนที่มีคะแนนตามที่กำหนด
        for (int i = 0; i < count;i++) {
            if (data[i].total >= minRange && data[i].total <= maxRange) {
                // นักเรียนมีคะแนนอยู่ในขอบเขต จึงแสดงข้อมูลนักเรียน
                countData++;
                printData(data[i]);
            }
        }
        printf("Count: %d\n", countData);
        // ถามความต้องผู้ใช้ ว่าต้องการงานอีกครั้งหรือไม่
        rewind(stdin);
        printf("\nDo you want to search again ? [Y/n]: ");
        scanf("%c", &again);
    // หากคำสั่งตรงเริ่มลูปใหม่อีกครั้ง
    }while(again == 'y' || again == 'Y');
}

// ค้นหานักเรียนที่มีเกรดที่กำหนด
void Search_by_grade (studentData data[], int count)
{
    char again;
    char grade[3];
    do
    {
        // รับขอบเขต
        rewind(stdin);
        system("cls");
        printf("Enter grade A, B+, B, C+, C, D+, D, F or 0 for Exit: ");
        scanf("%2s", &grade);
        // ตรวจสอบว่ามีการกำหนดเกรด
        if (strcmp(grade, "0") != 0) {
            // ลูปค้นหานักเรียน
            int countData = 0;
            for (int i = 0; i < count;i++) {
                // นักเรียนมีเกรดตรงกำหนด
                if (strcmp(data[i].grade, grade) == 0)
                {
                    // แสดงข้อมูลนักเรียนและนับจำนวนเพิ่มขึ้น
                    countData++;
                    printData(data[i]);
                }
            }
            // แสดงจำนวนทั้งหมด
            printf("Count: %d\n", countData);
            rewind(stdin);
            // ถามคำถามการใช้งานอีกรอบ
            printf("\nDo you want to search again ? [Y/n]: ");
            scanf("%c", &again);
        }
    // หากคำสั่งตรงเริ่มลูปใหม่อีกครั้ง
    }while(strcmp(grade, "0") != 0 && (again == 'y' || again == 'Y'));

}

// ค้นหานักเรียนที่มีชื่อตรงหรือคล้ายที่กำหนด
void Search_by_name (studentData data[], int count)
{
    char again;
    double minRange, maxRange;
    do
    {
        // รับชื่อ
        rewind(stdin);
        system("cls");
        char name[20];
        printf("Search name: ");
        scanf("%20s", &name);
        // ตรวจสอบชื่อที่รับมาไม่ได้ว่างเปล่า
        if (strcmp(name, "0") != 0) {
            // ลูปค้นหานักเรียน
            int countData = 0;
            for (int i = 0; i < count;i++) {
                // นักเรียนมีชื่อตรง หรือมีบางส่วนตรง
                if (strstr(data[i].name, name) != NULL)
                {
                    // แสดงผลและนับจำนวนเพิ่มขึ้น
                    countData++;
                    printData(data[i]);
                }
            }
            printf("Count: %d\n", countData);
            rewind(stdin);
            // ถามคำถามการใช้งานอีกครั้ง
            printf("\nDo you want to search again ? [Y/n]: ");
            scanf("%c", &again);
        }
    // หากคำสั่งตรงเริ่มลูปใหม่อีกครั้ง
    }while(again == 'y' || again == 'Y');

}

// ฟังก์ชันแสดงผลเมนูและรับคำสั่ง
int menu ()
{
    printf("**************************************************\n");
    printf("*                      Menu                      *\n");
    printf("*            [1] Read file                       *\n");
    printf("*            [2] Calculate grade                 *\n");
    printf("*            [3] Statistic                       *\n");
    printf("*            [4] List                            *\n");
    printf("*            [5] List sort by score              *\n");
    printf("*            [6] List sort by id                 *\n");
    printf("*            [7] List score range                *\n");
    printf("*            [8] List grade range                *\n");
    printf("*            [9] List search name                *\n");
    printf("*                                                *\n");
    printf("*            [0] Exit                            *\n");
    printf("**************************************************\n");
    printf("Select: ");
    // ส่งค่าคำสั่งไปใช้งาน
    return getint(0, 9);
}

// ฟังก์ชันในส่วนแสดงผลของเมนูต่างๆ
void display (int menu)
{
    system("cls");
    if (menu == 1) { // เมนูอ่านไฟล์
        read_file("score.csv", &studentCount);
    } else if (file_loaded == 0) // ตรวจสอบไฟล์มาได้รับการโหลดแล้ว หากยังไม่โหลดไฟล์จะใช้งานเมนูอื่นไม่ได้และแสดงข้อความให้โหลดไฟล์ก่อน
        printf("You need to load file first !");
    else if (menu == 2) { // เมนูคำนวณเกรด
        printf("Enter grade score: A, B+, B, C+, C, D+, D: ");
        int a, bplus, b, cplus, c, dplus, d;
        // กำหนดคะแนนขั้นต่ำของเกรดต่างๆ
        scanf("%d,%d,%d,%d,%d,%d,%d: ", &a, &bplus, &b, &cplus, &c, &dplus, &d);
        // เริ่มคำนวณเกรด
        calculate_grade(student, studentCount, a, bplus, b, cplus, c, dplus, d);
        // แสดงผลสถิติ
        showStatistic();
    } else if (menu == 3) { // เมนูแสดงข้อมูลสถิติ
        showStatistic();
    } else if (menu == 4) { // เมนูแสดงรายชื่อนักเรียนทั้งหมด
        DisplayList(student, studentCount);
    } else if (menu == 5) { // เมนูแสดงรายชื่อนักเรียนทั้งหมด เรียงตามคำแนนจากมากไปน้อย
        Sort_by_score(student, studentCount);
        DisplayList(student, studentCount);
    } else if (menu == 6) { // เมนูแสดงรายชื่อนักเรียนทั้งหมด เรียงตามรหัสจากน้อยไปมาก
        Sort_by_id(student, studentCount);
        DisplayList(student, studentCount);
    } else if (menu == 7) { // เมนูแสดงรายชื่อนักเรียนตามขอบเขตคะแนนที่กำหนด
        Search_by_score(student, studentCount);
    } else if (menu == 8) { // เมนูแสดงนักเรียนตามเกรดที่กำหนด
        Search_by_grade(student, studentCount);
    } else if (menu == 9) { // เมนูแสดงรายชื่อนักเรียนที่เหมือน
        Search_by_name(student, studentCount);
    }

}

// ฟังก์ชันหลักของการทำงาน
int main ()
{
    char again;
    int select;
    do {
        // แสดงเมนูหลักและรับคำสั่ง
        rewind(stdin);
        system("cls");
        select = menu();
        // ทำงานตามเมนูที่เลือก
        display(select);
        if (select != 0)
        {
            // เมื่อคำสั่งไม่ใช่ 0
            // หลังจากทำงานตามคำสั่งเสร็จ
            // เพื่อไม่ให้กลับไปที่หน้าเมนูหลักทันทีจะหยุดรอจนกว่าผู้ใช้งานจะกด enter
            char input;
            rewind(stdin);
            do
            {
                printf("\n\nPress [ENTER] to back to menu.");
                input = getchar();
            } while(input != '\n');
        }
    } while (select != 0); // หากคำสั่งไม่ใช่ 0 เริ่มต้นลูปใหม่
    return 0;
}
