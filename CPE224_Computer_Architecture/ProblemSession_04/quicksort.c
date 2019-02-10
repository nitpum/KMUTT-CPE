#include <stdio.h>


int quicksort (int nums[], int low, int high, int round)
{
  int pivot = nums[low], i, j;
  // Paritioning
  for (i =low + 1, j =low; i < high; i++)
  {
    if (nums[i] <= pivot)
    {
      j++;
      int x = nums[j];
      nums[j] = nums[i];
      nums[i] = x;
      //printf("Swap %d, %d : %d  : %d | %d\n", i, j,  nums[i], nums[j], pivot);
    }
  }
  // Swap pivot
  int x = nums[low];
  nums[low] = nums[j];
  nums[j]  = x;
  printf("\n%d) ", round);
  for (i = 0; i < 9; i++)
  {
    printf("%d, ", nums[i]);
  }
  if (low < high)
  {
      quicksort(nums, low, j - 1, round + 1);
      quicksort(nums, j + 1, high, round + 2);
  }
}

int main ()
{
  int nums[9] = {54, 26, 93, 17, 77, 31, 44, 55, 20}, i = 0;
  quicksort(nums, 0, 9, 0);
  return 1;
}
