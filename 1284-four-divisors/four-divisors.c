#include <math.h>

int sumFourDivisors(int* nums, int numsSize) {
    int totalSum = 0;

    for (int k = 0; k < numsSize; k++) {
        int n = nums[k];
        int divCount = 0;
        int divSum = 0;

        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                int j = n / i;

                divCount++;
                divSum += i;

                if (i != j) {
                    divCount++;
                    divSum += j;
                }

                if (divCount > 4)
                    break;
            }
        }

        if (divCount == 4)
            totalSum += divSum;
    }

    return totalSum;
}
