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

int oneComple (int n) {
  return n;
}

int twoComple (int n) {
  return n;
}

void printBinary (int binary[], int count) {
  int i;
  for (i = count-1; i >= 0; i--) {;
    printf("%d", binary[i]);
  }
  printf("\n");
}

int main () {

  int a, f[4];
  int test[4];
  scanf("%d", &a);
  toBinary(a, test);
  printf("======> %s\n", test);
  printf("> %d \n", a);
  printf("1 => %d\n", oneComple(a));
  toBinary(twoComple(a), f);
  printf("2 => ");
  printBinary(f, 4);
  return 0;
}
