#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct node {
    char value[20];
    struct node * next;
    struct node * prev;
} node;

node *sfirst;
node *slast;

node *qfirst;
node *qlast;

// Number stack;
node *nfirst;
node *nlast;

double ans = 0;

void to_lower_string(char *s) {
    int i; for (i = 0; s[i]; i++) s[i] = tolower(s[i]);
}
int is_number(char *s) {
    double num;
    char buff[40];
    strcpy(buff, s);
    int i, dotCount, negative = 0;
    // Check negative
    if (buff[0] == '-') negative = 1;
    if (negative) {
        int i;
        for (i = 0; i <  strlen(buff) - 1;i++) {
            buff[i] = buff[i + 1];
        }
        buff[strlen(buff)] = '\0';
    }

    // Check digit
    for (i=0; i < strlen(buff); i++) {
        if (isdigit(buff[i])==0 && buff[i] != '.')
            return 0;
    }
    // Check format for double or float
    i = dotCount = 0;
    for (i = 0; i < strlen(buff); i++) {
        if (buff[i] == '.') dotCount++;
    }
    if (dotCount < 2) return 1;
    else return 0;
}

void add_space (char *s) {
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

void remove_space_at_border (char * s) {
    while(s[strlen(s) - 1] == ' ') s[strlen(s) - 1] = '\0'; // Remove space in back
    while (s[0] == ' ') strcpy(s, s + 1); // Remove space in front
}

void space_split (char *s, char data[][40], int *count) {
    char * word;
    word = strtok(s, " ");
    while (word != NULL) {
        strcpy(data[*count], word);
        *count = *count + 1;
        //printf("data[%d] = %s\n", *count - 1, word);
        word = strtok(NULL, " ");
    }
    data[*count][0] = '\0';
}

int is_function (char *s) {
    const char fnList[11][10] = {"sin", "cos", "tan", "asin", "acos", "atan", "sqrt", "log", "exp", "pow", "abs"};
    int i;
    for (i=0;i<11;i++) {
        if (strcmp(s, fnList[i])==0)
            return 1;  // If string is equal function name return 1(TRUE)
    }
    return 0;
}

int is_sign (char * s) {
    int i;
    char list[4][10] = {"ans", "pi", "g", "e"};
    for (i = 0; i < 4; i++) {
        if (strcmp(s, list[i]) == 0) return 1;
    }
    return 0;
}


int is_operation (char *s) {
    if(strcmp(s, "+") == 0) return 1;
	if(strcmp(s, "-") == 0) return 1;
	if(strcmp(s, "*") == 0) return 2;
	if(strcmp(s, "/") == 0) return 2;
	if(strcmp(s, "^") == 0) return 3;
	return 0;
}

void space_combine (char data[][40], int *count) {
    int i;
    for (i = 0; i < *count; i++) {
        if (data[i] != '\0') {
            if (strcmp(data[i], "-") == 0) {
                if (
                    is_number(data[i+1]) &&
                        (
                         (i - 1 >= 0 && (strcmp(data[i-1],"(") == 0 || strcmp(data[i-1], "^") == 0 )) || i - 1 < 0
                        )
                    ) {
                    char buff[40];
                    strcpy(buff, "-");
                    strcat(buff, data[i+1]);
                    strcpy(data[i], buff);
                    int j;
                    for (j = i + 1; j < *count - 1; j++ ) {
                        strcpy(data[j], data[j+1]);
                    }
                    data[*count][0] = '\0';
                    *count = *count - 1;
                }
            }
        }
    }
}

int valid_parentheses (char data[][40], int *count) {
    int i, open, close;
    for (i = 0, open = close = 0; i < *count; i++) {
        if (strcmp(data[i], "(") == 0) open++;
        if (strcmp(data[i], ")") == 0) {
            close++;
            if (close > open) {
                return 0; // Invalid
            }
        }
    }
    if (open != close) {
        return 0; // Invalid
    }
    return 1; // valid
}

int check_next_valid (char * c, char * next) {
    if (is_number(c)) {
        //printf("%s, number\n", c);
        if (next == NULL) return 1;
        if ((is_operation(next) || strcmp(next, ")") == 0 || strcmp(next, "") == 0) && strcmp(next, "(") != 0 ) return 1;
    } else if (is_operation(c)) {
        //printf("%s, operation\n", c);
        if (next == NULL) return 0; // Invalid
        if (is_number(next) || strcmp(next, "(") == 0 || is_function(next) || is_sign(next)) return 1;
    } else if (is_function(c)) {
        //printf("%s, function\n", c);
        if (next == NULL) return 0; // Invalid
        if (strcmp(next, "(") == 0) return 1;
    } else if (is_sign(c)) {
        //printf("%s, sign\n", c);
        if (next == NULL || is_operation(next) || strcmp(next, ")") == 0) return 1;
        if (is_number(next) || is_function(next) || strcmp(next, "(") == 0 || strcmp(next, ")") == 0) return 1;
    } else if (strcmp(c, "(") == 0) {
        //printf("%s, (\n", c);
        if (next == NULL) return 0; // Invalid
        if (strcmp(next, "(") == 0 || is_function(next) || is_number(next) || is_sign(next)) return 1;
    } else if (strcmp(c, ")") == 0) {
        //printf("%s, )\n", c);
        if (next == NULL) return 1;
        if (is_operation(next) || strcmp(next, ")") == 0 || strcmp(next, "") == 0 || strcmp(next, "\0") == 0) return 1;
    }
    // Invalid
    //printf("%s -> %s\n", c, next);
    return 0;
}

void print_data (char data[][40], int *count) {
    int i;
    for (i = 0; i < *count; i++) {
        printf("data[%d] = %s\n", i, data[i]);
    }
}

double token_to_number (char *s) {
    if (s == NULL) return 0;
    if (is_sign(s)) {
        if (strcmp(s, "pi") == 0) {
            return M_PI;
        } else
        if (strcmp(s, "ans") == 0) {
            return ans;
        }
    } else
    if (is_number(s)) {
        return atof(s);
    }
    return 0;
}

void push_stack (char *s) {
    node *ptr = (node * )malloc(sizeof(node));
    strcpy(ptr->value, s);
    if (sfirst == NULL) {
        sfirst = slast = ptr;
    } else {
        slast->next = ptr;
        ptr->prev = slast;
        slast = ptr;
    }
}
node * pop_stack () {
    if (slast == NULL) return NULL;
    node * prev = sfirst;
    if (sfirst == slast) {
        sfirst = slast = NULL;
        return prev;
    }
    node * tmp = slast;
    while (prev->next != NULL && prev->next != slast) {
        prev = prev->next;
    }
    prev->next = NULL;
    slast = prev;
    return tmp;
}

void push_nstack (char *s) {
    node *ptr = (node * )malloc(sizeof(node));
    strcpy(ptr->value, s);
    if (nfirst == NULL) {
        nfirst = nlast = ptr;
    } else {
        nlast->next = ptr;
        ptr->prev = nlast;
        nlast = ptr;
    }
}
node * pop_nstack () {
    if (nlast == NULL) return NULL;
    node * prev = nfirst;
    if (nfirst == nlast) {
        nfirst = nlast = NULL;
        return prev;
    }
    node * tmp = nlast;
    while (prev->next != NULL && prev->next != nlast) {
        prev = prev->next;
    }
    prev->next = NULL;
    nlast = prev;
    return tmp;
}

void push_queue (char *s) {
    node *ptr = (node * )malloc(sizeof(node));
    strcpy(ptr->value, s);
    if (qfirst == NULL) {
        qfirst = ptr;
    } else {
        qlast->next = ptr;
    }
    qlast = ptr;
}

node * pop_queue () {
    node *ptr = qfirst;
    if (qfirst == qlast)
        qfirst = qlast = NULL;
    else
        qfirst = qfirst->next;
    return ptr;
}

void clear_stack () {
    while (qfirst != NULL) {
        pop_stack();
    }
}

void clear_nstack () {
    while (nfirst != NULL) {
        pop_nstack();
    }
}

void clear_queue () {
    while (qlast != NULL) {
        pop_queue();
    }
}

void add_parenthese (char data[][40], int *count) {
    strcpy(data[*count], ")");
    *count = *count+1;
    int i;
    for (i = *count; i > 0;i--) {
        strcpy(data[i], data[i-1]);
    }
    strcpy(data[0], "(");
    *count = *count+2;
    strcpy(data[*count+1], "\0");
}

void infix_to_postfix (char data[][40], int count) {
    int i;
    for (i = 0; i < count;i ++) {
        if (strcmp(data[i], "(") ==0 ){
            push_stack(data[i]);
        } else
        if (is_number(data[i])) {
            push_queue(data[i]);
        } else
        if (is_operation(data[i]) > 0) {
            while   (
                        slast != NULL &&
                        (
                            is_sign(slast->value) == 1 || is_function(slast->value) == 1 || ( is_operation(slast->value) && is_operation(data[i]) <= is_operation(slast->value))
                        )
                    ) {
                node * ptr = pop_stack();
                if (ptr != NULL) {
                    push_queue(ptr->value);
                }
            }
            push_stack(data[i]);
        } else
        if (is_function(data[i])) {
            push_stack(data[i]);
        } else
        if (is_sign(data[i])) {
            push_stack(data[i]);
        } else
        if (strcmp(data[i], ")") ==0 ){
            while (slast != NULL && strcmp(slast->value, "(") != 0) {
                node * ptr = pop_stack();
                if (ptr != NULL) {
                    push_queue(ptr->value);
                }
            }
            if (slast != NULL && strcmp(slast->value, "(") == 0) {
                pop_stack();
            }
        }
    }
    while (slast != NULL) {
        node * ptr = pop_stack();
        if (ptr != NULL) {
            push_queue(ptr->value);
        }
    }
}

void print_stack (node * first) {
    printf("[ Print stack ]\n");
    node * ptr = first;
    int i = 1;
    while (ptr != NULL) {
        printf("%d: %s\n", i++, ptr->value);
        ptr = ptr->next;
    }
}

void postfix_to_array (char result[][40], int *count) {
    *count = 0;
    while (qfirst != NULL) {
        node * ptr = pop_queue();
        strcpy(result[*count], ptr->value);
        *count = *count + 1;
    }
    strcpy(result[*count],"\0");
}

void calculate (char data[][40], int *count, int *error) {
    clear_queue();
    clear_stack();
    clear_nstack();
    int i;

    for ( i = 0; i < *count; i++) {
        if (is_number(data[i]) || is_sign(data[i])) {
            push_nstack(data[i]);
        } else
        if (is_operation(data[i])) {
            double
                a = token_to_number(pop_nstack()),
                b = token_to_number(pop_nstack()),
                tmp = 0;
            if (strcmp(data[i], "+") == 0) tmp = b + a;
            else if (strcmp(data[i], "-") == 0) tmp = b - a;
            else if (strcmp(data[i], "*") == 0) tmp = b * a;
            else if (strcmp(data[i], "/") == 0) {
                if (a == 0)
                    *error = *error + 1;
                else
                    tmp = b / a;
            }
            else if (strcmp(data[i], "^") == 0) {
                if (a == 0 && b == 0) *error = *error + 1;
                else tmp = pow(b, a);
            }
            char s[50];
            sprintf(s, "%lf", tmp);
            push_nstack(s);
        } else
        {
            double a = token_to_number(pop_nstack()), tmp;
            if (is_function(data[i])) {
                if (strcmp(data[i], "sin") == 0) tmp = sin(a*M_PI/180);
                else if (strcmp(data[i], "cos") == 0) tmp = cos(a*M_PI/180);
                else if (strcmp(data[i], "tan") == 0) tmp = tan(a*M_PI/180);
                else if (strcmp(data[i], "asin") == 0) tmp = asin(a)*180/M_PI;
                else if (strcmp(data[i], "acos") == 0) tmp = acos(a)*180/M_PI;
                else if (strcmp(data[i], "atan") == 0) tmp = atan(a)*180/M_PI;
                else if (strcmp(data[i], "sqrt") == 0) tmp = sqrt(a);
                else if (strcmp(data[i], "exp") == 0) tmp = exp(a);
                else if (strcmp(data[i], "log") == 0) tmp = log(a);
                else if (strcmp(data[i], "abs") == 0) tmp = fabs(a);
            }
            char s[50];
            sprintf(s, "%lf", tmp);
            push_nstack(s);
        }
    }

    ans = token_to_number(pop_nstack());
    //print_stack(nfirst);
}

int main () {

    char input[100], data[100][40];
    ans = 0;
    do
    {
        int dataCount = 0;
        rewind(stdin);
        strcpy(input, "");
        clear_queue();
        clear_stack();
        printf("expression> ");
        gets(input);
        add_space(&input);
        remove_space_at_border(&input); // Remove space
        to_lower_string(&input); // Fix case insensitive
        if (strcmp(input, "help") == 0) {
            printf("answer> token = sin,cos,tan,asin,acos,atan,sqrt,log,exp,abs+,-,*,/,^,(,),pi,ans\n");
        } else if (strcmp(input, "end") != 0){
            space_split(&input, data, &dataCount);
            space_combine(data, &dataCount);
            int i = 0, error = 0;
            //print_data(data, &dataCount);
            for (i = 0; strcmp(data[i], "") != 0; i++) {
                if (i + 1 >= dataCount) {
                    error += !check_next_valid(data[i], NULL);
                } else {
                    error += !check_next_valid(data[i], data[i + 1]);
                }
            }
            if (valid_parentheses(data, &dataCount) == 0) {
                //printf("parentheses\n");
                error += 1;
            }
            if (error > 0) {
                printf("answer> Error\n");
            } else {
                printf("answer> Ok\n");

                infix_to_postfix(data, dataCount);
                char postfix[50][40];
                int postfixCount = 0, i = 0;
                postfix_to_array(postfix, &postfixCount);
                calculate(postfix, &postfixCount, &error);

                if (error > 0) {
                    printf("answer> Error\n");
                } else {
                    printf("answer> %g\n", ans);
                }
            }

        }

    } while(strcmp(input, "end") != 0);

    printf("End program\n");
    printf("Program writen by 60070501029 Nitipoom Unrrom");

    return 1;
}
