#include <stdio.h>

#define MAX_BIT 4

void toBinary (int decimal, int binary[]) {
  int i = 0;
  if (decimal < 0) decimal *= -1;
  for (i = 0; i < 4; i++) {
    binary[i] = (decimal > 1)? decimal % 2: decimal;
    decimal /= 2;
  }
}

void invertBinary (int binary[]) {
  int i; for (i = 0; i < MAX_BIT; i++) binary[i] = !binary[i];
}

void toSigned (int decimal, int binary[], int negative) {
  int i;
  toBinary((negative)? decimal * -1: decimal, binary);
  binary[3] = negative;
}

void oneComple (int decimal, int binary[], int negative) {
  int i;
  toBinary((negative)? decimal * -1: decimal, binary);
  if (negative) invertBinary(binary);
}

void twoComple (int decimal, int binary[], int negative) {
  int i, j, plus;
  if (negative) decimal *= -1;
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

void printBinary (int binary[], int count, int overflow) {
  int i;
  if (overflow) return printf("Overflow!\n");
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
        char input[8];
        int number, overflow = 0, neg;
        int binary[MAX_BIT];
        rewind(stdin);

        printf("====================\n");
        printf("Enter number: ");
        scanf("%s", &input);
        sscanf(input, "%d", &number);
        neg = input[0] == '-';
        overflow = (number > 7 || number < -8);

        printf("Binary: ");
        toBinary(number, binary);
        printBinary(binary, MAX_BIT, overflow);
        printf("Signed-Magnitude: ");
        toSigned(number, binary, neg);
        printBinary(binary, MAX_BIT, overflow);
        printf("1'Complement: ");
        oneComple(number, binary, neg);
        printBinary(binary, MAX_BIT, overflow);
        printf("2'Complement: ");
        twoComple(number, binary, neg);
        printBinary(binary, MAX_BIT, overflow);

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
