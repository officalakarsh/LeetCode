

int minOperations(int* nums, int numsSize, int k) {
    long long sum = 0;

    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }

    int r = sum % k;
    return r;   
}
