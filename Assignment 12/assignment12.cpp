#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_COLUMN 30
#define MAX_ROW 30

char command[50];
char params[3][30];
int paramsCount = 0;

// Set string to lower alphabet
void ToLower(char *s) {
    for (int i = 0;s[i];i++) s[i] = tolower(s[i]);
}

// Split command and parameters and keep to variable
void SplitCommand (char cmd[]) {
    paramsCount = 0; // Reset count

    strcpy(params[0], ""); // Reset
    strcpy(params[1], ""); // Reset
    strcpy(params[2], ""); // Reset
    // Get command and parameters
    sscanf(cmd, "%s %s %s %s", command, params[0], params[1], params[2]);
    // Count parameter
    if (strcmp(params[0], "") != 0) paramsCount++;
    if (strcmp(params[1], "") != 0) paramsCount++;
    if (strcmp(params[2], "") != 0) paramsCount++;
    // Set command to lower for easily check
    ToLower(command);
}

int ReadFile (char *filename, int matrix[][MAX_COLUMN], int *row, int *column)
{
    FILE *file;
    int a;
    if ((file = fopen(filename, "r")) != NULL)
    {
        char line[20][30];
        int lineCount = 0;

        printf("[add] read file %s \n", filename);
        // Count line
        while (!feof(file))
        {
            if (fgets(line[lineCount], sizeof(line[lineCount]), file))
            {
                lineCount++;
            }
        }

        // Get row and column
        *row = 0;
        *column = 0;
        sscanf(line[0], "%d %d", row, column);
        // Set matrix data
        int i;
        for (i = 0; i < *row; i++) // LOOP ROW
        {
            char *token = strtok(line[i + 1], " "); // Split by space
            for (int j = 0; j < *column && token != NULL; j++) // LOOP COLUMN
            {
                matrix[i][j] = atoi(token);
                token = strtok(NULL, " ");
            }
        }

        fclose(file);
    } else {
        printf("[error] can't read file.\n");
        return 0;
    }
    return 1;
}

void WriteFile (char *filename, int matrix[][MAX_COLUMN], int row, int column)
{
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        // Write row and column
        fprintf(file, "%d %d\n", row, column);
        for (int i = 0; i < row; i++) // LOOP ROW
        {
            for (int j = 0; j < column; j++) // COLUMN
            {
                fprintf(file, "%d ", matrix[i][j]); // Write each column
            }
            fprintf(file, "\n"); // New line for next row
        }
        fclose(file);
    }
    else {
        printf("[error] can't write file.\n");
    }
}

// Show martix data
void ShowMatrix (int matrix[][MAX_COLUMN], int row, int column)
{
    printf("MATRIX: %d x %d\n", row, column);
    for (int i = 0; i < row; i++) // ROW
    {
        for (int j = 0; j < column; j++) // COLUMN
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void Transpose (int matrix[][MAX_COLUMN], int *row, int *column)
{
     // Copy original and transpose matrix
    int data[*row][MAX_COLUMN];
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++)
        {
            data[i][j] = matrix[i][j]; // transpose
        }
    }
    // Transpose row and column
    int _column = * row;
    *row = *column;
    *column = _column;
    // Set transposed matrix
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++)
        {
            matrix[i][j] = data[j][i];
        }
    }
}

// Check input command that have to enough parameters
// return 0 if have not enough parameters
// return 1 if have enough parameters
int CommandCheck (char *cmd, int *errorParams, int param = 0)
{
    if (strcmp(command, cmd) == 0)
    {
        if (param == paramsCount) // Don't have enough parameters
        {
            *errorParams = -1;
            return 1;
        }
        else
        {
            char c[50];
            printf("[error] need %d parameter\n", param);
            *errorParams = 1;
            return 0;
        }
    }
    else return 0;
}

// All command
void Command (char *cmd)
{
    int errorParams = 0;
    if (CommandCheck("clear", &errorParams))
    {
        // Clear screen
        system("cls");
    }
    else if (CommandCheck("show", &errorParams, 1))
    {
         // Show matrix from file
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        if (ReadFile(params[0], matrix, &row, &column))
            ShowMatrix(matrix, row, column);
    }
    else if (CommandCheck("transpose", &errorParams, 2))
    {
        // Transpose matrix
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        if (ReadFile(params[0], matrix, &row, &column))
        {
            ShowMatrix(matrix, row, column);
            Transpose(matrix, &row, &column);
            ShowMatrix(matrix, row, column);
            WriteFile(params[1], matrix, row, column);
        }
    }
    else if (CommandCheck("add", &errorParams, 3))
    {
        // Combine two matrix
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        int bMatrix[MAX_ROW][MAX_COLUMN];
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn)) // Read matrix A
        {
            if (ReadFile(params[1], bMatrix, &bRow, &bColumn)) // Read matrix B
            {
                // Check A and B is same row and same column
                if (aRow != bRow || aColumn != bColumn)
                {
                    // Matrix not same size
                    printf("[error] two matrix not the same size.\n");
                }
                else
                {
                    // A and B are same size then combine to C
                    int cMartix[aRow][MAX_COLUMN];
                    for (int i = 0; i < aRow; i++)
                    {
                        for (int j = 0; j < aColumn; j++)
                        {
                            cMartix[i][j] = aMatrix[i][j] + bMatrix[i][j];
                        }
                    }
                    // Print matrix C
                    ShowMatrix(cMartix, aRow, aColumn);
                    // Write file
                    WriteFile(params[2], cMartix, aRow, aColumn);
                }
            }
        }
    }
    else if (CommandCheck("remove", &errorParams, 3))
    {
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        int bMatrix[MAX_ROW][MAX_COLUMN];
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn)) // Read matrix A
        {
            if (ReadFile(params[1], bMatrix, &bRow, &bColumn)) // Read matrix B
            {
                if (aRow != bRow || aColumn != bColumn)
                {
                    printf("[error] two matrix not the same size.\n");
                }
                else
                {
                    int cMartix[aRow][MAX_COLUMN];
                    for (int i = 0; i < aRow; i++)
                    {
                        for (int j = 0; j < aColumn; j++)
                        {
                            cMartix[i][j] = aMatrix[i][j] - bMatrix[i][j];
                        }
                    }
                    ShowMatrix(cMartix, aRow, aColumn);
                    WriteFile(params[2], cMartix, aRow, aColumn);
                }
            }
        }
    }
    else if (CommandCheck("multipy", &errorParams, 3))
    {
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;
        int aMatrix[MAX_ROW][MAX_COLUMN];
        if (ReadFile(params[0], aMatrix, &aRow, &aColumn))
        {
            int cMartix[aRow][MAX_COLUMN];
            printf("%d", atoi(params[1]));
            for (int i = 0; i < aRow; i++)
            {
                for (int j = 0; j < aColumn; j++)
                {
                    cMartix[i][j] = aMatrix[i][j] * atoi(params[1]);
                }
            }
            ShowMatrix(cMartix, aRow, aColumn);
            WriteFile(params[2], cMartix, aRow, aColumn);
        }
    }
    else if (CommandCheck("det", &errorParams, 1))
    {
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        if (ReadFile(params[0], matrix, &row, &column)) // Read matrix file
        {
            // row and column must be same size for det
            if (row == column)
            {
                // Print matrix
                ShowMatrix(matrix, row, column);

                int a = 0, b = 0;
                // Lower
                for (int j = 0; j < column; j++)
                {
                    int line = matrix[0][j];
                    for (int i = 1; i < row; i++)
                    {
                        line = line * matrix[i][(j + i)%(column)];
                    }
                    a += line;
                }
                // Upper
                for (int j = 0; j < column; j++)
                {
                    int line = matrix[row-1][j];
                    for (int i = row - 2; i >= 0; i--)
                    {
                        line = line * matrix[i][(j + ((row-1) - i))%(column)];
                    }
                    b += line;
                }
                // Print det value
                printf("Det is %d \n", a - b);
            }
            else
            {
                printf("[error] matrix must be same size.\n");
            }
        }
    }

    if (errorParams == 0)
        printf("[error] commmand not found.\n");
}

int main ()
{

    do
    {
        rewind(stdin);
        printf("> ");
        char cmd[100];
        gets(cmd);
        SplitCommand(cmd); // Split command
        if (strcmp(command, "end") != 0 && strcmp(command, "exit") != 0)
            Command(command); // Check command action
    } while(strcmp(command, "end") != 0 && strcmp(command, "exit") != 0);

    return 0;
}
