#include <stdio.h>
#include <string.h>

char command[50];
char arg[3][30];
int argCount = 0;

void spiltcmd (char cmd[])
{

    printf("Split");
    char _arg[3][30];
    char temp[80], tempCMD;
    strcpy(temp, cmd);
    sprintf(*temp, "%s", tempCMD, _arg[0], _arg[1], _arg[2]);
    int count = 0;

    printf("\nCommand: %s\n", command);

    if (strcmp(_arg[0], "") != 0) count++;
    if (strcmp(_arg[1], "") != 0) count++;
    if (strcmp(_arg[2], "") != 0) count++;

    printf("\n%d\n", count);

    /*
    while (word != NULL)
    {
        strcpy(arg[argCount++], strtok(NULL, " "));
    }*/
    /*
    printf("Done ! ");

    int i;
    for (i = 0; i < count; i++)
    {
        printf("%d %s\n", i, _arg[i]);
    }
*/
}

int main ()
{
    spiltcmd("test");

    return 0;
}
