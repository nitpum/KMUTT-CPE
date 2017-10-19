#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
char temp[100];

int IsValidIndentifier (char *s) {
    if (!isalpha(s[0]) && s[0] != '_')
        return 0;
    else {
        int i;
        for (i = 1; i < strlen(s);i++) {
            if (!isalpha(s[i]) && s[i] != '_' && isdigit(s[i]) == 0)
                return 0;
        }
    }
    return 1;
}

int IsNumber(char *s) {
    double num;
    int i;
    for (i=0; i < strlen(s); i++) {
        if (isdigit(s[i])==0 && s[i] != '.')
            return 0;
    }
    return IsValidNumberFormat(s); // If c1 and c2 == null that mean no any character then check number format
}

int IsValidNumberFormat (char *s) {
    int dotCount = 0, i = 0;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '.') dotCount++;
    }
    if (dotCount < 2) return 1;
    else return 0;
}

int IsFunction (char *s) {
    const char fnList[10][10] = {"sin", "cos", "tan", "asin", "acos", "atan", "sqrt", "log", "exp", "pow"};
    int i;
    for (i=0;i<10;i++) {
        if (strcmp(s, fnList[i])==0)
            return 1;  // If string is equal function name return 1(TRUE)
    }
    return 0;
}

int IsOperation (char *s) {
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (strchr(",+-*/^()", s[i]) != NULL)
            return 1;
    }
    return 0;
}

void AddSpace (char *s) {
    int i,j;
    char temp[200] = "", old[200] = "";
    for (i=0,j=strlen(s); i < j;i++) {
        if (strchr(",+-*/^()", s[i]) != NULL)
            sprintf(temp,"%s %c ", old, s[i]);
        else
            sprintf(temp,"%s%c",old, s[i]);
        strcpy(old, temp);
    }
    strcpy(s,temp);
}

void SpaceSeparate (char *s, char data[][40]) {
    char * word;
    int count = 0;
    word = strtok(s, " ");
    while (word != NULL) {
        strcpy(data[count++], word);
        word = strtok(NULL, " ");
    }
    data[count][0] = '\0';
}

void ToLower(char *s) {
    int i;
    for (i = 0;s[i];i++) s[i] = tolower(s[i]);
}

int main ()
{
    printf("Enter input: ");
    gets(input);
    do
    {
        char temp[100], data[100][40];
        int errorCount = 0, fnCount = 0, opCount = 0, idCount =0, numCount = 0;

        printf("Input: %s\n", input);
        strcpy(temp, input); // Copy input to temp for operation
        ToLower(temp); // Set to lower
        printf("To lower: %s\n", temp);
        AddSpace(temp);
        printf("Add space: %s\n", temp);
        SpaceSeparate(temp, data);
        int i;
        for (i=0; i < sizeof(data) && strcmp(data[i],"")!=0;i++) {
            if (IsFunction(data[i])) {
                printf("%s : FUNCTION\n", data[i]);
                fnCount++;
            }
            else if (IsNumber(data[i])) {
                printf("%s : NUMBER\n", data[i]);
                numCount++;
            }
            else if (IsOperation(data[i])) {
                printf("%s : OPERATION\n", data[i]);
                opCount++;
            }
            else if (IsValidIndentifier(data[i])) {
                printf("%s : INDENTIFIER \n", data[i]);
                idCount++;
            }
            else {
                errorCount++;
                printf("%s : ERROR \n", data[i]);
            }
        }
        printf("\n ===  RESULT  === \n Number: %d \n Operation: %d \n Function: %d \n Identifier: %d \n Error: %d \nTotal: %d", numCount, opCount, fnCount, idCount, errorCount, numCount + opCount + fnCount + errorCount + idCount);

        printf("\n\n");
        printf("Enter input: ");
        gets(input);
    } while (strcmp(input, "end")!=0 && strcmp(input, "exit")!=0);

    printf("\nEnd");

    return 0;
}
