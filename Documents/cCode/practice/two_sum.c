#include <stdio.h>
#include <stdlib.h>

/* int* twoSum(int* nums, int numsSize, int target){ */
/*     int num_1; */
/*     int num_2; */
/*     int* result = malloc(sizeof(int)*2); */
/*      */
/*     for (int i = 0; i < numsSize + 1; i++) { */
/*         num_1 = nums[i]; */
/*         for (int j = i + 1; j < numsSize + 1; j++) { */
/*             num_2 = nums[j]; */
/*             if (num_1 + num_2 == target) { */
/*               result[0] = i; */
/*               result[1] = j; */
/*             } */
/*         } */
/*     }       */
/*     return result; */
/*         */
/* } */

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int num_1;
    int num_2;
    int* result = (int*)malloc(sizeof(int)*2);
    
    for (int i = 0; i < numsSize; i++) {
        num_1 = nums[i];
        for (int j = i + 1; j < numsSize; j++) {
            num_2 = nums[j];
            if (num_1 + num_2 == target) {
              result[0] = i;
              result[1] = j;
            }
        }
    }      
    return result;
       
}

int main()
{
  int nums[8] = {1, 2, 3, 8, 2, 5, 78, 4};
  int* results = malloc(sizeof(int)*2);
  int ret_size;
  results = twoSum(nums, 7, 8, &ret_size);
  for (int i = 0; i < 3; i++) printf("%i\n", results[i]);
  free(results);
  return 0;
}
