class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> best(m, vector<int>(n, -1));
        queue<pair<int,int>> q;

        int startHealth = health - grid[0][0];
        if (startHealth <= 0) return false;

        q.push({0, 0});
        best[0][0] = startHealth;

        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            int curHealth = best[x][y];
            if (x == m - 1 && y == n - 1) return true;

            for (auto &d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;

                int nextHealth = curHealth - grid[nx][ny];
                if (nextHealth <= 0) continue;

                if (nextHealth > best[nx][ny]) {
                    best[nx][ny] = nextHealth;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }
};