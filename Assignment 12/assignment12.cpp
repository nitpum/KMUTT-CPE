#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// กำหนดขนาดแถวและคอลลั่มสูงสุด
#define MAX_COLUMN 30
#define MAX_ROW 30

// ตัวแปรเก็บชือคำสั่งและพารามิเตอร์
char command[50];
char params[3][30];
int paramsCount = 0;

// ฟังก์ชันเซต string ให้อักษรภาษาอังกฤษเป็นตัวพิมพ์เล็กทั้งหมด
void ToLower(char *s) {
    for (int i = 0;s[i];i++) s[i] = tolower(s[i]);
}

// ฟังก์ชันวิเคราะห์คำสั่งที่พิมพ์มา โดยแบ่ง string แล้วเก็บเป็นชื่อคำสั่งและพารามิเตอร์
void SplitCommand (char cmd[]) {
    paramsCount = 0; // รีเซตจำนวนพารามิเตอร์
    // ลบค่าพารามิเตอร์อันเดิม
    strcpy(params[0], "");
    strcpy(params[1], "");
    strcpy(params[2], "");
    // นำ string มาแยกส่วนต่างๆ เก็บเป็นชื่อคำสั่งและพารามิเตอร์
    sscanf(cmd, "%s %s %s %s", command, params[0], params[1], params[2]);
    // นับจำนวนพารามิเตอร์
    if (strcmp(params[0], "") != 0) paramsCount++;
    if (strcmp(params[1], "") != 0) paramsCount++;
    if (strcmp(params[2], "") != 0) paramsCount++;
    // นำชื่อคำสั่งไปเข้าฟังก์ชันทำเป็นตัวพิมพ์เล็กเพื่อง่ายต่อการเช็ค
    ToLower(command);
}

// ฟังก์ชันอ่านข้อมูลเมตริกในไฟล์แล้วเก็บลงอาเรย์
int ReadFile (char *filename, int matrix[][MAX_COLUMN], int *row, int *column)
{
    FILE *file;
    int a;
    // อ่านและตรวจสอบการเปิดไฟล์
    if ((file = fopen(filename, "r")) != NULL)
    {
        char line[20][30];
        int lineCount = 0;

        printf("[add] read file %s \n", filename);
        // ลูปไปจนกว่าจะจบไฟล์
        while (!feof(file))
        {
            if (fgets(line[lineCount], sizeof(line[lineCount]), file))
            {
                // นับจำนวนบรรทัดเพิ่ม
                lineCount++;
            }
        }

        // รีเซตขนาดแถวและคอลลั่ม
        *row = 0;
        *column = 0;
        // อ่านขนาดแถวและคอลลั่มจากบรรทัดแรกสุด
        sscanf(line[0], "%d %d", row, column);
        // เริ่มกำหนดค่าลงเมตริก
        int i;
        for (i = 0; i < *row; i++) // ลูปแต่ละแถว
        {
            char *token = strtok(line[i + 1], " "); // แยกข้อมูลด้วยเว้นวรรค
            for (int j = 0; j < *column && token != NULL; j++) // ลูปแต่ละคอลลั่ม
            {
                matrix[i][j] = atoi(token); // นำข้อมูลที่แยกได้มาแปลงเป็นตัวเลขเก็บลงเมตริก
                token = strtok(NULL, " "); // เลื่อนไปหาข้อมูลตัวถัดไป
            }
        }

        fclose(file);
    } else { // แสดงข้อความเปิดไฟล์ไม่ได้
        printf("[error] can't read file.\n");
        return 0; // อ่านไม่สำเร็จ
    }
    return 1; // อ่านสำเร็จ
}

// ฟังก์ชันบันทึกเมตริกลงเป็นไฟล์
void WriteFile (char *filename, int matrix[][MAX_COLUMN], int row, int column)
{
    // เขียนไฟล์
    FILE *file = fopen(filename, "w");
    if (file != NULL) // ตรวจสอบว่าเขียนไฟล์ได้
    {
        // บันทึกขนาดแถวและขนาดคอลลั่มลงบรรทัดแรก
        fprintf(file, "%d %d\n", row, column);
        // เริ่มบันทึกข้อมูลเมตริก
        for (int i = 0; i < row; i++) // ลูปข้อมูลแต่ละแถว
        {
            for (int j = 0; j < column; j++) // ลูปข้อมูลคอลลัมในแถว
            {
                fprintf(file, "%d ", matrix[i][j]); // บันทึกข้อมูลในหนึ่งแถวแยกคอลลั่มโดยการเว้นวรรค
            }
            fprintf(file, "\n"); // ขึ้นบรรทัดใหม่สำหรับแถวถัดไป
        }
        fclose(file);
    }
    else { // แสดงข้อความเมื่อเปิดไฟล์ไม่ได้
        printf("[error] can't write file.\n");
    }
}

// ฟังก์ชันแสดงข้อมูลที่อยู่ในเมตริก
void ShowMatrix (int matrix[][MAX_COLUMN], int row, int column)
{
    printf("MATRIX: %d x %d\n", row, column);
    for (int i = 0; i < row; i++) // ลูปแถว
    {
        for (int j = 0; j < column; j++) // ลูปข้อมูลคอลลัมในแถว
        {
            printf("%d ", matrix[i][j]); 
        }
        printf("\n"); // ขึ้นบรรทัดใหม่สำหรับแถวถัดไป
    }
}

// ฟังก์ชัน Transpose เมตริก
void Transpose (int matrix[][MAX_COLUMN], int *row, int *column)
{
     // สร้างเมตริกเพื่อใช้เก็บค่าที่ transpose 
    int data[*row][MAX_COLUMN];
    // ลูปแถวของเมตริกเดิม
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++) // ลูปคอลลัมของเมตริกเดิม
        {
            data[i][j] = matrix[i][j]; // Transpose แล้วเก็บค่าไว้ในเมตริกใหม่
        }
    }
    // สลับขนาดแถวและคอลลัม
    int _column = * row;
    *row = *column;
    *column = _column;
    // เซ็ตค่าเมตริกใหม่ทับเมตริกเดิม
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++)
        {
            matrix[i][j] = data[j][i];
        }
    }
}

// ตรวจสอบความถูกต้องของคำสั่งว่าใส่พารามิเตอร์ตรงกับคำสั่งหรือไม่
// cmd คือชื่อคำสั่ง
// param คือจำนวนพารามิเตอร์ที่ต้องการ
// return 0 ถ้าพารามิเตอร์ไม่ครบ
// return 1 เมื่อพารามิเตอร์ครบ
int CommandCheck (char *cmd, int *errorParams, int param = 0)
{
    if (strcmp(command, cmd) == 0)
    {
        if (param == paramsCount) // จำนวนพารามิเตอร์ที่พิมพ์ต้องตรงตามที่กำหนด
        {
            *errorParams = -1; // กำหนด errorParams เป็น -1 เพื่อบอกว่าเจอคำสั่งแล้ว
            return 1; // พารามิเตอร์ครบ
        }
        else
        {
            char c[50];
            printf("[error] need %d parameter\n", param); // แสดงข้อความบอกจำนวนพารามิเตอร์ที่ต้องใส่
            *errorParams = 1; // กำหนดเพื่อบอกว่ามี error
            return 0;
        }
    }
    else return 0;
}

// ฟังก์ชันตรวจสอบคำสัง
void Command (char *cmd)
{
    // ประกาศตัวแปรไว้ตรวจสอบว่าเจอคำสั่งแล้วและมี error
    int errorParams = 0;

    // ตรวจหาคำสั่งโดยใช้ฟังก์ชัน CommandCheck เมื่อเจอ(return 1)จะทำงานแค่ในส่วนนั้นและไม่หาคำสั่งอื่นต่อ
    if (CommandCheck("clear", &errorParams)) // คำสั่งล้างหน้าจอ
    {
        system("cls");
    }
    else if (CommandCheck("show", &errorParams, 1))
    {
         // คำสั่งแสดงผลเมตริก
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        // ตรวจสอบวการอ่านเมตริกก่อน หากสำเร็จค่อยแสดงผล
        if (ReadFile(params[0], matrix, &row, &column))
            ShowMatrix(matrix, row, column);
    }
    else if (CommandCheck("transpose", &errorParams, 2))
    {
        // คำสั่ง Transpose เมตริก
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        // ตรวจสอบการอ่านเมตริกก่อน หากสำเร็จจึงทำงาน
        if (ReadFile(params[0], matrix, &row, &column))
        {
            // แสดงเมตริกก่อนและหลัง transpose จากนั้นบันทึกไฟล์
            ShowMatrix(matrix, row, column);
            Transpose(matrix, &row, &column);
            ShowMatrix(matrix, row, column);
            WriteFile(params[1], matrix, row, column);
        }
    }
    else if (CommandCheck("add", &errorParams, 3))
    {
        // ฟังก์ชันบวกเมตริก
        // สร้างเมตริก 2 เมตริก
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        int bMatrix[MAX_ROW][MAX_COLUMN];
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn)) // ต้องอ่านไฟล์ 1 สำเร็จจึงดำเนินการต่อ
        {
            if (ReadFile(params[1], bMatrix, &bRow, &bColumn)) // ต้องอ่านไฟล์ 2 สำเร็จจึงดำเนินการต่อ
            {
                // ตรวจสอบขนาดแถวและคอลลัม
                if (aRow != bRow || aColumn != bColumn)
                {
                    // หากขนาดไม่เท่ากันจะหยุดการทำงานและแสดงข้อความ
                    printf("[error] two matrix not the same size.\n");
                }
                else
                {
                    // มีขนาดเท่ากันทำงานต่อ
                    // สร้างเมตริกใหม่มาไว้เก็บค่า
                    int cMartix[aRow][MAX_COLUMN];
                    // ลูปข้อมูลแต่ละตัวในเมตริกใหม่
                    for (int i = 0; i < aRow; i++)
                    {
                        for (int j = 0; j < aColumn; j++)
                        {
                            // บวกเมตริก A และ B เก็บไว้ในเมตริกใหม่
                            cMartix[i][j] = aMatrix[i][j] + bMatrix[i][j];
                        }
                    }
                    // แสดงข้อมูลเมตริกใหม่
                    ShowMatrix(cMartix, aRow, aColumn);
                    // บันทึกไฟล์
                    WriteFile(params[2], cMartix, aRow, aColumn);
                }
            }
        }
    }
    else if (CommandCheck("remove", &errorParams, 3))
    {
        // คำสั่งนำสองเมตริกมาลบกัน
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        int bMatrix[MAX_ROW][MAX_COLUMN];
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn)) // ต้องอ่านไฟล์ที่ 1 สำเร็จจึงดำเนินการต่อ
        {
            if (ReadFile(params[1], bMatrix, &bRow, &bColumn)) // ต้องอ่านไฟล์ที่ 2 สำเร็จจึงดำเนินการต่อ
            {
                // ขนาดแถวและคอลลั่มต้องเท่ากัน
                if (aRow != bRow || aColumn != bColumn)
                {
                    // ขนาดแถวและคอลลัมไม่เท่ากัน แสดงข้อความ error
                    printf("[error] two matrix not the same size.\n");
                }
                else
                {
                    // สร้างเมตริกใหม่มาเก็บข้อมูล
                    int cMartix[aRow][MAX_COLUMN];
                    // เริ่มการลบเมตริก
                    for (int i = 0; i < aRow; i++)
                    {
                        for (int j = 0; j < aColumn; j++)
                        {
                            // ลบเมตริกแล้วเก็บลงเมตริกใหม่
                            cMartix[i][j] = aMatrix[i][j] - bMatrix[i][j];
                        }
                    }
                    // แสดงผลและเขียนไฟล์
                    ShowMatrix(cMartix, aRow, aColumn);
                    WriteFile(params[2], cMartix, aRow, aColumn);
                }
            }
        }
    }
    else if (CommandCheck("multipy", &errorParams, 3))
    {
        // คำสั่งคูณเมตริก
        int aRow = 0, aColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        // ต้องอ่านไฟล์สำเร็จจึงดำเนินการต่อ
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn)) 
        {
            // สร้างเมตริกมาเก็บเมตริกที่คูณ
            int cMartix[aRow][MAX_COLUMN];
            printf("%d", atoi(params[1]));
            for (int i = 0; i < aRow; i++)
            {
                for (int j = 0; j < aColumn; j++)
                {
                    cMartix[i][j] = aMatrix[i][j] * atoi(params[1]); // คูณเมตริกด้วยพารามิเตอร์ที่ 2 แล้วเก็บลงเมตริกใหม่
                }
            }
            // แสดงผลและเขียนไฟล์
            ShowMatrix(cMartix, aRow, aColumn);
            WriteFile(params[2], cMartix, aRow, aColumn);
        }
    }
    else if (CommandCheck("det", &errorParams, 1))
    {
        // คำสั่ง Determinant
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        if (ReadFile(params[0], matrix, &row, &column)) // ต้องอ่านไฟล์สำเร็จจึงดำเนินการต่อ
        {
            // ตรวจสอบขนาดของแถวและคอลลัมต้องเท่ากัน
            if (row == column)
            {
                // แสดงข้อมูล
                ShowMatrix(matrix, row, column);
                // คำนวณเมตริกโดนใช้สูตร ล่าง - บน
                int a = 0, b = 0;
                // ล่าง
                for (int j = 0; j < column; j++)
                {
                    int line = matrix[0][j];
                    for (int i = 1; i < row; i++)
                    {
                        // นำข้อมูลจากบนขวาลงล่างมาคูณกัน
                        line = line * matrix[i][(j + i)%(column)];
                    }
                    a += line; // นำข้อมูลที่คุณกันแต่ละชุดมาบวกัน
                }
                // บน
                for (int j = 0; j < column; j++)
                {
                    int line = matrix[row-1][j];
                    for (int i = row - 2; i >= 0; i--)
                    {
                        // นำข้อมูลจากล่างขึ้นขวาบนมาคูณกัน
                        line = line * matrix[i][(j + ((row-1) - i))%(column)];
                    }
                    b += line; // นำข้อมูลที่คุณกันแต่ละชุดมาบวกกัน
                }
                // แสดงผลลัพ
                printf("Det is %d \n", a - b);
            }
            else
            {   // แสดงข้อความหากขนาดแถวและคอลลัมไม่เท่ากัน
                printf("[error] matrix must be same size.\n");
            }
        }
    }

    // หาก errorParams เท่ากับ 0 แสดงว่าไม่พบชื่อคำสั่งที่พิมพ์มา
    if (errorParams == 0)
        printf("[error] commmand not found.\n");
}

int main ()
{    
    do
    {
        // รับคำสั่งใหม่
        rewind(stdin);
        printf("> ");
        char cmd[100];
        gets(cmd);
        // นำคำสั่งมาวิเคราะห์
        SplitCommand(cmd);
        // หากคำสั่งไม่ใช่ end exit ให้ทำงาน
        if (strcmp(command, "end") != 0 && strcmp(command, "exit") != 0)
            Command(command);

    // หากคำสั่งคือ end exit จึงจบการทำงาน แต่ถ้าไม่ใช่จะเริ่มทำงานลูปต่อไป
    } while(strcmp(command, "end") != 0 && strcmp(command, "exit") != 0);

    return 0;
}
