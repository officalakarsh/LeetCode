#include <stddef.h>

int countPartitions(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    long long totalSum = 0;
    for (int i = 0; i < numsSize; ++i) totalSum += nums[i];

    if ((totalSum & 1) == 0) {
        return numsSize - 1;
    } else {
        return 0;
    }
}
