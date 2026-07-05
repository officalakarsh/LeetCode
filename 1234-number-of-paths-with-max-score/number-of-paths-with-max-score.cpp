class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1000000007;

        vector<vector<int>> score(n, vector<int>(n, -1));
        vector<vector<long long>> ways(n, vector<long long>(n, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X') continue;
                if (i == n - 1 && j == n - 1) continue;

                int best = -1;
                long long cnt = 0;

                vector<pair<int, int>> dir = {{1, 0}, {0, 1}, {1, 1}};

                for (auto &d : dir) {
                    int ni = i + d.first;
                    int nj = j + d.second;

                    if (ni >= n || nj >= n) continue;
                    if (score[ni][nj] == -1) continue;

                    if (score[ni][nj] > best) {
                        best = score[ni][nj];
                        cnt = ways[ni][nj];
                    } else if (score[ni][nj] == best) {
                        cnt = (cnt + ways[ni][nj]) % MOD;
                    }
                }

                if (best == -1) continue;

                int val = 0;
                if (board[i][j] >= '1' && board[i][j] <= '9')
                    val = board[i][j] - '0';

                score[i][j] = best + val;
                ways[i][j] = cnt % MOD;
            }
        }

        if (ways[0][0] == 0)
            return {0, 0};

        return {score[0][0], (int)(ways[0][0] % MOD)};
    }
};