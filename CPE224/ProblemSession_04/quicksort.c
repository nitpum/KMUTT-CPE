#include <stdio.h>


int quicksort (int nums[], int low, int high)
{
  int pivot = nums[low], i, j;
  // Paritioning Lomuto
  for (i =low + 1, j =low; i < high; i++)
  {
    if (nums[i] <= pivot)
    {
      j++;
      int x = nums[j];
      nums[j] = nums[i];
      nums[i] = x;
    }
  }
  // Swap pivot value
  int x = nums[low];
  nums[low] = nums[j];
  nums[j]  = x;
  // Recursive
  if (low < high)
  {
      quicksort(nums, low, j - 1);
      quicksort(nums, j + 1, high);
  }
}

int main ()
{
  int nums[9] = {54, 26, 93, 17, 77, 31, 44, 55, 20}, i = 0;
  quicksort(nums, 0, 9);
  // Print result
  for (i = 0; i < 9; i++)
  {
    printf("%d ", nums[i]);
  }
  return 1;
}
