#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node_number {
    double value;
    struct node_number * next;
} linkedlist ;

int listCount;
linkedlist *first;
linkedlist *last;

void toLower(char *s) {
    int i; for (i = 0; s[i]; i++) s[i] = tolower(s[i]);
}
int is_number(char *s) {
    double num;
    int i, dotCount, negative = 0;
    for (i=0; i < strlen(s); i++) {
        if (s[0] == '-')
        {
        }
        else if (isdigit(s[i])==0 && s[i] != '.')
            return 0;
    }
    // Check format for double or float
    i = dotCount = 0;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] == '.') dotCount++;
    }
    if (dotCount < 2) return 1;
    else return 0;
}

void getparameter (char input[], char cmd[], char param[][20], int *paraCount) {
    *paraCount = 0;
    // Clear old string
    strcpy(cmd,  "");
    char tmpPara[50], tmpPara2[50];
    int inputCount;
    inputCount = sscanf(input, "%s%[^\n]", cmd, tmpPara);
    if (inputCount >= 2) {
        char tmpStr[20];
        //printf("Param %s\n", tmpPara);

        int  i = 0, end = 0, c = 0;
        do
        {
            //printf("Scan %s\n", tmpPara);
            c = sscanf(tmpPara, "%s%[^\n]", tmpStr, tmpPara2);
            strcpy(param[*paraCount], tmpStr);
            //printf(">%s\n", tmpStr);
            strcpy(tmpPara, tmpPara2);
            tmpPara2[0] = '\0'; // Clear buffer
            *paraCount = *paraCount + 1;
            //printf("\nC: %d\n", c);
            if (c == 1 || (c == 1 && tmpPara[0] == ' ')) end = 1;
            //printf("\nEnd: %d\n", end);
        } while(tmpPara[0] != '\0' && tmpPara[0] != '\n' && tmpPara != NULL && end == 0);

    }
}

int command (char name[], int needParam, char cmd[], int paraCount, int *err) {
    if (strcmp(name, cmd) == 0) {
        if (needParam > 0) {
            if (paraCount != needParam) {
                *err = 1;
                return 1;
            }
        } else if (needParam == -1) {
            if (paraCount < 1) {
                *err = 1;
                return 1;
            }
        } else if (paraCount > 0) {
            *err = 1;
            return 1;
        }
        *err = 0;
        return 1;
    }
    return 0; // not this command
}

int is_sorted ()
{
    linkedlist * current = first;
    if (current->next != NULL) {
        if (current->value > current->next->value)
            return 0;
        current = current->next;
    }
    return 1;
}

void print_list () {
    if (first != NULL) {
        printf("list>");
        linkedlist * current;
        current = first;
        do
        {
            printf(" %g", current->value);
            current = current->next;
        } while(current != NULL);
        printf("\n");
    } else {
        printf("list> NULL\n");
    }
}

void add_node (double value) {
    linkedlist * node;
    node = (linkedlist *) malloc(sizeof(linkedlist));
    node->next = NULL;
    node->value = value;
    if (first == NULL) {
        first = last = node;
    }
    else {
        last->next = node;
        last = node;
    }
    listCount++;
}

void remove_node (linkedlist * prev, linkedlist * current) {
    if (prev != NULL)       prev->next = current->next;
    if (current == first)   first = current->next;
    if (current == last) {
        last = prev;
        if (last != NULL) last->next = NULL;
    }
    listCount--;
}

void swap_node (linkedlist * a, linkedlist * b) {
    double tmp_value = a->value;
    a->value = b->value;
    b->value = tmp_value;
}

void sorted () {
    linkedlist * i = first;
    printf("first: %g\n", first->value);
    while (i != NULL) {
        linkedlist * j = i->next;
        while (j != NULL) {
            if (i->value > j->value)
                swap_node(i, j);
            j = j->next;
        }
        i = i->next;
    }
}

int main () {
    char cmd[50];
    int count = 0, err, programEnd = 0;
    listCount = 0;
    do
    {
        rewind(stdin);
        char input[100], cmd[20], param[20][20];
        int paraCount = 0;
        err = -1;
        print_list();
        printf("command> ");
        gets(input);
        getparameter(input, cmd, param, &paraCount);
        //printf("\nCount: %d", paraCount);
        if (command("list", 0, cmd, paraCount, &err) && err == 0)
            print_list();
        else if (command("add", -1, cmd, paraCount, &err) && err == 0) {
            // Check all param is number
            int i;
            for (i = 0; i < paraCount; i++) {
                if (is_number(param[i]) == 0) {
                    i = paraCount; // End
                    err = 1;
                }
            }
            if (err == 0) {
                for (i = 0; i < paraCount; i++) {
                    double value;
                    sscanf(param[i], "%lf", &value);
                    add_node(value);
                }
            }
        }
        else if (command("peek", 1, cmd, paraCount, &err) && err == 0) {
            if (is_number(param[0]) == 0) {
                err = 1;
            } else {
                if (listCount <= 0)
                {
                    printf("anwser> current list is empty\n");
                } else {
                    if (atoi(param[0]) == 0) {
                        printf("anwser> %g\n", first->value);
                    } else if (atoi(param[0]) == -1) {
                        printf("anwser> %g\n", last->value);
                    } else if (atoi(param[0]) < listCount) {
                        int i;
                        linkedlist * current = first;
                        for (i = 0; i < atoi(param[0]);i++) {
                            if (i < atoi(param[0]))
                            current = current->next;
                        }
                        printf("anwser> %g\n", current->value);
                    } else if (atoi(param[0]) >= listCount) {
                        printf("anwser> Maximum peek is %d\n", listCount-1);
                    }
                }
            }
        }
        else if (command("delete", 1, cmd, paraCount, &err) && err == 0) {
            // Check all param is number
            int i;
            for (i = 0; i < paraCount; i++) {
                if (is_number(param[i]) == 0) {
                    i = paraCount; // End
                    err = 1;
                }
            }
            // All parameter is number
            if (err == 0) {
                if (listCount <= 0) {
                    printf("anwser> current list is empty\n");
                } else {
                    int end = 0, found = 0;
                    linkedlist * current = first;
                    linkedlist * prev = NULL;
                    double value;
                    sscanf(param[0], "%lf", &value);
                    do
                    {
                        if (current->value != value) {
                            prev = current;
                            current = current->next;
                        } else { // Found
                            printf("anwser> %g found enter y to confirm: ", value);
                            char confirm[20];
                            scanf("%s", confirm);
                            if (strcmp(confirm, "y") == 0 || strcmp(confirm, "Y") == 0) {
                                found++;
                                remove_node(prev, current);
                                current = current->next;
                            }
                        }
                    } while(current != NULL && end != 1);

                    if (found == 0) {
                        printf("anwser> %g not found\n", value);
                    }


                }
            }
        }
        else if (command("push", 1, cmd, paraCount, &err) && err == 0) {
            int i;
            for (i = 0; i < paraCount; i++) {
                if (is_number(param[i]) == 0) {
                    i = paraCount; // End
                    err = 1;
                }
            }
            // All parameter is number
            if (err == 0) {
                if (listCount <= 0) {
                    printf("anwser> current list is empty\n");
                } else {
                    double value;
                    sscanf(param[0], "%lf", &value);
                    linkedlist *node;
                    node = (linkedlist *) malloc(sizeof(linkedlist));
                    node->next = first;
                    node->value = value;
                    first = node;
                    listCount++;
                }
            }
        }
        else if (command("pop", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("anwser> current list is empty\n");
            } else {
                remove_node(NULL, first);
            }
        }
        else if (command("sqrt", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("anwser> current list is empty\n");
            } else {
                first->value = sqrt(first->value);
            }
        }
        else if (command("rec", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
            printf("answer> current list is empty\n");
            } else {
                first->value = 1 / first->value;
            }
        }
        else if (command("neg", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
            printf("answer> current list is empty\n");
            } else {
                first->value = -1 * first->value;
            }
        }
        else if (command("+", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("answer> current list is empty\n");
            } else if (listCount >= 2) {
                first->value =  first->next->value - first->value;
                remove_node(first, first->next);
            } else {
                printf("answer> Can't operation\n");
            }
        }
        else if (command("-", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("answer> current list is empty\n");
            } else if (listCount >= 2) {
                first->value = first->next->value - first->value ;
                remove_node(first, first->next);
            } else {
                printf("answer> Can't operation\n");
            }
        }
        else if (command("*", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("answer> current list is empty\n");
            } else if (listCount >= 2) {
                first->value = first->next->value * first->value ;
                remove_node(first, first->next);
            } else {
                printf("answer> Can't operation\n");
            }
        }
        else if (command("/", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("answer> current list is empty\n");
            } else if (listCount >= 2) {
                first->value = first->next->value / first->value ;
                remove_node(first, first->next);
            } else {
                printf("answer> can't operation\n");
            }
        }
        else if (command("pow", 0, cmd, paraCount, &err) && err == 0) {
            if (listCount <= 0) {
                printf("answer> current list is empty\n");
            } else if (listCount >= 2) {
                first->value = pow(first->next->value, first->value);
                remove_node(first, first->next);
            } else {
                printf("answer> can't operation\n");
            }
        }
        else if (command("insert", 1, cmd, paraCount, &err) && err == 0) {
             int i;
            for (i = 0; i < paraCount; i++) {
                if (is_number(param[i]) == 0) {
                    i = paraCount; // End
                    err = 1;
                }
            }
            // All parameter is number
            if (err == 0) {
                if (listCount <= 0) {
                    printf("answer> current list is empty\n");
                } else {
                    if (is_sorted() == 0) {
                        printf("answer> can't insert before sort\n");
                    } else {
                        linkedlist * node;
                        node = (linkedlist *) malloc(sizeof(linkedlist));
                        node->value = atof(param[0]);
                        if (first == NULL) {
                            first = last = node;
                        }
                        else if (first->value > node->value) {
                            node->next = first;
                            first = node;
                        } else {
                            linkedlist * current = first;
                            while (current->next != NULL && current->next->value < atof(param[0])) {
                                current = current->next;
                            }
                            node->next = current->next;
                            current->next = node;
                            if (current == last)
                                last = node;
                        }
                    }
                }
            }
        }
        else if (command("sort", 0, cmd, paraCount, &err) && err == 0) {
            sorted();
        }
        else if (command("help", 0, cmd, paraCount, &err) && err == 0) {
            printf("answer> list of command\n");
            printf(" - add\n - peek\n - delete\n - push\n - pop\n - sqrt\n - rec\n - neg\n - [+]\n - [-]\n - [*]\n - [/]\n - pow\n - insert \n - sort\n - help\n - end\n");
        }
        else if (command("end", 0, cmd, paraCount, &err) && err == 0) {
            programEnd = 1;
        }

        if (!(strcmp(cmd, "end") == 0 )) {

            if (err == -1)      printf("answer> syntax error\n");
            else if (err >= 1) printf("answer> parameters error \n");
        }

    } while (programEnd == 0 );

    printf("End program\n");
    printf("Program writen by 60070501029 Nitipoom Unrrom");
}
