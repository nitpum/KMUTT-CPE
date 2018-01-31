#include <stdio.h>
#include <string.h>
#include <ctype.h>


void toLower(char *s) {
    int i;
    for (i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

int isnumber(char s[]) {
    double num;
    int i, count = 0;
    for (i=0; i < strlen(s); i++) {
        if (isdigit(s[i])==0) {
            return 0;
        } else  {
            count++;
        }
    }
    return count;
}

int getparameter (char input[], char cmd[], char p1[], char p2[], char p3[]) {
    int paraCount = 0;
    // Clear old string
    strcpy(cmd,  "");
    strcpy(p1,  "");
    strcpy(p2,  "");
    strcpy(p3,  "");
    // Split command
    sscanf(input, "%s %s %s %s", cmd, p1, p2, p3);
    // Check parameter count
    if (strcmp(p1, "") != 0) paraCount++;
    if (strcmp(p2, "") != 0) paraCount++;
    if (strcmp(p3, "") != 0) paraCount++;
    return paraCount;
}


int command (char name[], int paraCount, int minDigit, char cmd[], char p1[], char p2[], char p3[], int pCount, int * err) {

    if (strcmp(name,cmd) == 0) {
        if (minDigit > 0 && paraCount <= pCount) {
            if (paraCount >= 1 && isnumber(p1) == 0) *err = 1;
            if (paraCount >= 2 && isnumber(p2) == 0) *err = 1;
            if (paraCount >= 3 && isnumber(p3) == 0) *err = 1;

            int digitCount = 0;
            if (pCount >= 1) digitCount += isnumber(p1);
            if (pCount >= 2) digitCount += isnumber(p2);
            if (pCount >= 3) digitCount += isnumber(p3);
            if (digitCount < minDigit) *err = 1;

            if (*err == 1) return 1;

            *err = 0;
            return 1;

        } else
        if (paraCount == pCount) {
            if (paraCount >= 1 && isnumber(p1) == 0) *err = 1;
            if (paraCount >= 2 && isnumber(p2) == 0) *err = 1;
            if (paraCount >= 3 && isnumber(p3) == 0) *err = 1;

            if (*err == 1) return 1;

            *err = 0;
            return 1;
        }
        *err = 1;
        return 1;
    }

    return 0;
}

int main () {

    char cmd[50];
    int count, err;
    do
    {
        rewind(stdin);
        char input[100];
        printf("command> ");
        gets(input);
        char p1[50], p2[50], p3[50];
        count = 0;
        count = getparameter(input, cmd, p1, p2, p3);
        err = -1;
        toLower(cmd);
        if (command("list", 0, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("end", 0, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("sort", 0, 0, cmd, p1, p2, p3, count, &err)  && err == 0) printf("answer> OK\n");
        else if (command("pop", 0, 0, cmd, p1, p2, p3, count, &err)  && err == 0 ) printf("answer> OK\n");
        else if (command("delete", 1, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("push", 1, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("search", 1, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("insert", 1, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("peek", 1, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("add", 1, 2, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");
        else if (command("end", 0, 0, cmd, p1, p2, p3, count, &err) && err == 0) printf("answer> OK\n");

        if (err == -1)      printf("answer> syntax error\n");
        else if (err >= 1) printf("answer> parameters error \n");


    } while (!(strcmp(cmd, "end") == 0 && count == 0));

    printf("End program\n");
    printf("Program writen by 60070501029 Nitipoom Unrrom");

}
