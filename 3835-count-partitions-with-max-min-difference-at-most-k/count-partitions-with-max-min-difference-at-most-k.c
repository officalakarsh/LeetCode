#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

int countPartitions(int* nums, int n, int k) {
    long long* dp = (long long*)calloc(n + 1, sizeof(long long));
    long long* pref = (long long*)calloc(n + 1, sizeof(long long));

    dp[0] = 1;
    pref[0] = 1;

    int* dqMin = (int*)malloc(n * sizeof(int));
    int* dqMax = (int*)malloc(n * sizeof(int));
    int frontMin = 0, backMin = 0;
    int frontMax = 0, backMax = 0;

    int left = 0;

    for (int right = 0; right < n; right++) {

        while (backMin > frontMin && nums[dqMin[backMin - 1]] > nums[right])
            backMin--;
        dqMin[backMin++] = right;

        while (backMax > frontMax && nums[dqMax[backMax - 1]] < nums[right])
            backMax--;
        dqMax[backMax++] = right;

        while (nums[dqMax[frontMax]] - nums[dqMin[frontMin]] > k) {
            left++;
            if (dqMin[frontMin] < left) frontMin++;
            if (dqMax[frontMax] < left) frontMax++;
        }
        long long sum = pref[right] - (left == 0 ? 0 : pref[left - 1]);
        if (sum < 0) sum += MOD;
        dp[right + 1] = sum % MOD;

        pref[right + 1] = (pref[right] + dp[right + 1]) % MOD;
    }

    long long ans = dp[n] % MOD;
    free(dp);
    free(pref);
    free(dqMin);
    free(dqMax);
    return ans;
}
