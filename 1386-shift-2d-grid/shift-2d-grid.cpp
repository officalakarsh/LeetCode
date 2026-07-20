class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int total = m * n;

        k %= total;

        vector<vector<int>> ans(m, vector<int>(n));

        for (int i = 0; i < total; i++) {
            int newPos = (i + k) % total;

            int r1 = i / n;
            int c1 = i % n;

            int r2 = newPos / n;
            int c2 = newPos % n;

            ans[r2][c2] = grid[r1][c1];
        }

        return ans;
    }
};