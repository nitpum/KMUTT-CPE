#include <stdio.h>

void toBinary (int decimal, int binary[]) {
  int i = 0;
  if (decimal < 0) decimal *= -1;
  for (i = 0; decimal > 1; i++) {
    binary[i] = decimal % 2;
    decimal /= 2;
  }
  if (i < 4) binary[i++] = decimal;
  for (;i < 4;i++) binary[i] = 0;
}

void invertBinary (int binary[]) {
  int i = 0;
  for (i = 0; i < 4; i++) {
    if (binary[i] == 0) binary[i] = 1;
    else binary[i] = 0;
  }
}

void toSigned (int decimal, int binary[]) {
  int i, negative = 0;
  if (decimal < 0) {
    negative = 1;
    decimal *= -1;
  }
  toBinary(decimal, binary);
  if (negative == 1) binary[3] = 1;
  else binary[3] = 0;
}

void toSingle (int decimal, int binary[]) {
  int i, negative = 0;
  if (decimal < 0) {
    negative = 1;
    decimal *= -1;
  }
  toBinary(decimal, binary);
  if (negative == 1) invertBinary(binary);
}

void toSecond (int decimal, int binary[]) {
  int i, j, plus, negative = 0;
  if (decimal < 0) {
    negative = 1;
    decimal *= -1;
  }
  toBinary(decimal, binary);
  if (negative == 1) invertBinary(binary);
  for (j = 0, plus = 1; negative == 1 && plus == 1 && j < 4; j++) {
    if (binary[j] + plus > 1) {
      binary[j] = 0;
      plus = 1;
    } else {
      binary[j] += plus;
      plus = 0;
    }
  }
}

void printBinary (int binary[], int count) {
  int i;
  for (i = count-1; i >= 0; i--) {;
    printf("%d", binary[i]);
  }
  printf("\n");
}

int main () {
    int mode = 0;
    char again;
    do
    {
        int number, overflow = 0;
        int binary[4];
        rewind(stdin);
        printf("====================\n");
        printf("Enter number: ");
        scanf("%d", &number);
        if (number > 7 || number < -8) overflow = 1;
        printf("Binary: ");
        toBinary(number, binary);
        if (overflow) printf("Overflow!\n");
        else printBinary(binary, 4);
        printf("Signed-Magnitude: ");
        toSigned(number, binary);
        if (overflow) printf("Overflow!\n");
        else printBinary(binary, 4);
        printf("1'Complement: ");
        toSingle(number, binary);
        if (overflow) printf("Overflow!\n");
        else printBinary(binary, 4);
        printf("2'Complement: ");
        toSecond(number, binary);
        if (overflow) printf("Overflow!\n");
        else printBinary(binary, 4);
        printf("====================\n");
        printf("Again (Y/n) ?\n");
        do
        {
            rewind(stdin);
            printf("Enter Y/n: ");
            scanf("%c", &again);
        } while (again != 'y' && again != 'Y' && again != 'N' && again != 'n');
    } while (again == 'y' || again == 'Y');

    return 0;
}
