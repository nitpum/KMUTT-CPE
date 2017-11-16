#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_COLUMN 30
#define MAX_ROW 30

char command[50];
char params[3][30];
int paramsCount = 0;

void PrintInfo(char *msg, char *header = command)
{
    printf("[%s] %s \n", header, msg);
}

void ToLower(char *s) {
    int i;
    for (i = 0;s[i];i++) s[i] = tolower(s[i]);
}

void SplitCommand (char cmd[])
{
    // Reset params
    paramsCount = 0;

    strcpy(params[0], "");
    strcpy(params[1], "");
    strcpy(params[2], "");
    //
    sscanf(cmd, "%s %s %s %s", command, params[0], params[1], params[2]);
    // Count parameter
    if (strcmp(params[0], "") != 0) paramsCount++;
    if (strcmp(params[1], "") != 0) paramsCount++;
    if (strcmp(params[2], "") != 0) paramsCount++;

    ToLower(command);
}


int ReadFile (char *filename, int matrix[][MAX_COLUMN], int *row, int *column)
{
    FILE *file;
    int a;
    if ((file = fopen(filename, "r")) != NULL)
    {
        char newline;
        char line[20][30];
        int lineCount = 0;

        printf("Read file %s \n", filename);

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
        for (i = 0; i < *row; i++) // ROW
        {
            // COLUMN
            int space;
            char *token = strtok(line[i + 1], " ");
            for (int j = 0; j < *column && token != NULL; j++)
            {
                matrix[i][j] = atoi(token);
                token = strtok(NULL, " ");
            }
        }

        fclose(file);
    } else {
        PrintInfo("Can't read file.");
        return 0;
    }
    return 1;
}

void WriteFile (char *filename, int matrix[][MAX_COLUMN], int row, int column)
{
    FILE *file = fopen(filename, "w");
    if (file != NULL)
    {
        fprintf(file, "%d %d\n", row, column);
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                fprintf(file, "%d ", matrix[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
    else {
        PrintInfo("Can't write file.");
    }
}

void ShowMatrix (int matrix[][MAX_COLUMN], int row, int column)
{
    printf("MATRIX: %d x %d\n", row, column);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void Transpose (int matrix[][MAX_COLUMN], int *row, int *column)
{
    int data[*row][MAX_COLUMN];
    // Copy
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++)
        {
            data[i][j] = matrix[i][j];
        }
    }
    // Transpose
    int _column = * row;
    *row = *column;
    *column = _column;
    for (int i = 0; i < *row; i++)
    {
        for (int j = 0; j < *column; j++)
        {
            matrix[i][j] = data[j][i];
        }
    }
}


int CommandCheck (char *cmd, int *errorParams, int param = 0)
{
    if (strcmp(command, cmd) == 0)
    {
        if (param == paramsCount)
        {
            *errorParams = -1;
            return 1;
        }
        else
        {
            char c[50];
            sprintf(c, "Need %d parameter", param);
            PrintInfo(c);
            *errorParams = 1;
            return 0;
        }
    }
    else return 0;
}

void Command (char *cmd)
{
    int errorParams = 0;
    if (CommandCheck("clear", &errorParams))
    {
        system("cls");
    }
    else if (CommandCheck("hi", &errorParams))
    {
        PrintInfo("Hello");
    }
    else if (CommandCheck("show", &errorParams, 1))
    {
        int row = 0, column = 0;
        int matrix[30][MAX_COLUMN];
        if (ReadFile(params[0], matrix, &row, &column))
            ShowMatrix(matrix, row, column);
    }
    else if (CommandCheck("transpose", &errorParams, 2))
    {
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
        int aRow = 0, aColumn = 0;
        int bRow = 0, bColumn = 0;


    }

    if (errorParams == 0)
        PrintInfo("commmand not found");
}


int main ()
{
    do
    {
        rewind(stdin);
        printf("> ");
        char cmd[100];
        gets(cmd);
        SplitCommand(cmd);
        if (strcmp(command, "end") != 0 && strcmp(command, "exit") != 0)
            Command(command);
    } while(strcmp(command, "end") != 0 && strcmp(command, "exit") != 0);
    return 0;
}
