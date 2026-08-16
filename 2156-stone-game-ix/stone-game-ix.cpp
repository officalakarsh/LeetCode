class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int c0 = cnt[0];
        int c1 = cnt[1];
        int c2 = cnt[2];

        // Even number of stones divisible by 3
        if (c0 % 2 == 0) {
            return c1 > 0 && c2 > 0;
        }

        // Odd number of stones divisible by 3
        return abs(c1 - c2) > 2;
    }
};