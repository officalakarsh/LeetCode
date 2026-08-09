class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = sum of piles from i to n-1
        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        // dp[i][M] = maximum stones current player can get
        // starting from index i with M
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int M = 1; M <= n; M++) {

                // Current player can take all remaining piles
                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                // Try taking X piles
                for (int X = 1; X <= 2 * M && i + X <= n; X++) {

                    int nextM = max(M, X);

                    // Total remaining stones - opponent's best score
                    int currentScore =
                        suffix[i] - dp[i + X][nextM];

                    dp[i][M] = max(dp[i][M], currentScore);
                }
            }
        }

        return dp[0][1];
    }
};
