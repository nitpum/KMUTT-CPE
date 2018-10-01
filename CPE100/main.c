//
//  main.c
//  assignment-12
//
//  Created by Korbboon Thuswongsa on 15/11/2560 BE.
//  Copyright © 2560 Korbboon Thuswongsa. All rights reserved.
//

#include <stdio.h>
#include <string.h>

struct matrixStruct {
    double matrixArray[32][32];
    int row, col;
};

void matrixPrint(struct matrixStruct *matrixP) {
    int i, j;
    for (i = 0; i < matrixP->row; i++) {
        for (j = 0; j < matrixP->col; j++) {
            printf("%4.0lf", matrixP->matrixArray[i][j]);
        }
        printf("\n");
    }
}

void matrixWriteFs(struct matrixStruct *matrixP, char *path){
    FILE *fp;
    int i, j;
    
    char _path[200] = "/Users/korbboonthuswongsa/assignment-12/";//local path
    strcat(_path, path);//read path
    fp = fopen(_path, "w");
    
    fprintf(fp,"%d %d \n", matrixP->row, matrixP->col); //write header file
    for (i = 0; i < matrixP->row; i++) {
        for (j = 0; j < matrixP->col; j++) {
            fprintf(fp, "%4.0lf ", matrixP->matrixArray[i][j]); //write matrix file
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void matrixReadFs(struct matrixStruct *matrixP, char *path) {
    FILE *fp;
    int i, j, row = 0, col = 0;
    char _path[200] = "/Users/korbboonthuswongsa/assignment-12/";//local path
    strcat(_path, path);//read path
    
    fp = fopen(_path, "r");
    if (fp != NULL) { //read if file exist
        fscanf(fp, "%d%d", &row, &col); //read header file
        matrixP->row = row;
        matrixP->col = col; //write row col header to struct

        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                fscanf(fp, "%lf",&matrixP->matrixArray[i][j]);
            }
        }
    } else printf("file not found\n");
}

void matrixCopy(struct matrixStruct *matrixP, struct matrixStruct *matrixPO) {
    int i, j;
    
    matrixPO->col = matrixP->col;
    matrixPO->row = matrixP->row;
    for (i = 0; i < matrixP->row; i++) {
        for (j = 0; j < matrixP->col; j++) {
            matrixPO->matrixArray[i][j] = matrixP->matrixArray[i][j];
        }
    }
}

void matrixTrans(struct matrixStruct *matrixP, char *path) {
    struct matrixStruct temp;
    int i, j;
    temp.row = matrixP->col; //swap header file for matrixTrans
    temp.col = matrixP->row;
    for (i = 0; i < temp.row; i++) {
        for (j = 0; j < temp.col; j++) {
            temp.matrixArray[i][j] = matrixP->matrixArray[j][i];
        }
    }
    matrixWriteFs(&temp, path);
    matrixPrint(&temp);
}

void matrixPlusM(struct matrixStruct *matrixP1, struct matrixStruct *matrixP2, char *path, int op) {
    int i, j, k;
    struct matrixStruct temp;
    
    //operation toggle
    if (op == 1) { // 1 is substract
        k = -1;
    } else k = 1;
    
    if (matrixP1->col == matrixP2->col && matrixP1->row == matrixP2->row) {
        for (i = 0; i < matrixP1->row; i++) {
            for (j = 0; j < matrixP1->col; j++) {
                temp.matrixArray[i][j] = matrixP1->matrixArray[i][j] + matrixP2->matrixArray[i][j] * k;
            }
        }
        temp.col = matrixP1->col; //header initial
        temp.row = matrixP1->row;
        matrixWriteFs(&temp, path);
        matrixPrint(&temp);
    } else printf("cannot plus matrix\n");
}

void matrixMul(struct matrixStruct *matrixP1, struct matrixStruct *matrixP2, char *path) {
    int i, j, k;
    struct matrixStruct temp;
    
    if (matrixP1->col == matrixP2->row) {
        temp.row = matrixP1->row; //header initial
        temp.col = matrixP2->col;
        
        for(i = 0; i < matrixP1->row; i++) {
            for(j = 0; j < matrixP2->col; j++) {
                temp.matrixArray[i][j] = 0; //prvent from NULL value
                for(k = 0; k < matrixP1->col; k++) {
                    temp.matrixArray[i][j] += matrixP1->matrixArray[i][k] * matrixP2->matrixArray[k][j];
                }
            }
        }
        matrixPrint(&temp);
        matrixWriteFs(&temp, path);
    } else printf("cannot multiply\n");
}

struct matrixStruct matrixA;
struct matrixStruct matrixB;

void command() {

    int check = 0;
    char commandArray[100], para[1000], pathA[100], pathB[100], pathC[100], error[100];

    while (check == 0) {
        scanf("%s", commandArray); //input
        fgets(para, sizeof(para), stdin);
        
        if (strcmp(commandArray, "add") == 0 && sscanf(para, "%s %s %s %s", pathA, pathB, pathC, error) == 3) {
            matrixReadFs(&matrixA, pathA);
            matrixReadFs(&matrixB, pathB);
            matrixPlusM(&matrixA, &matrixB, pathC, 0);
        } else if (strcmp(commandArray, "sub") == 0 && sscanf(para, "%s %s %s %s", pathA, pathB, pathC, error) == 3) {
            matrixReadFs(&matrixA, pathA);
            matrixReadFs(&matrixB, pathB);
            matrixPlusM(&matrixA, &matrixB, pathC, 1);
        } else if (strcmp(commandArray, "tranpose") == 0 && sscanf(para, "%s %s %s", pathA, pathB, error) == 2) {
            matrixReadFs(&matrixA, pathA);
            matrixTrans(&matrixA, pathB);
        } else if (strcmp(commandArray, "show") == 0 && sscanf(para, "%s %s", pathA, error) == 1) {
            matrixReadFs(&matrixA, pathA);
            matrixPrint(&matrixA);
        }  else if (strcmp(commandArray, "multiply") == 0 && sscanf(para, "%s %s %s %s", pathA, pathB, pathC, error) == 3) {
            matrixReadFs(&matrixA, pathA);
            matrixReadFs(&matrixB, pathB);
            matrixMul(&matrixA, &matrixB, pathC);
        } else if ((strcmp(commandArray, "end") == 0 || strcmp(commandArray, "exit") == 0)) {
            printf("\nend program.");
            check = 1;
        } else printf("invalid please try again \n");
    }
}

int main() {
    
    command();

    return 0;
}
