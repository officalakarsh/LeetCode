class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();

        unordered_map<float, vector<float>> slopeIntercepts;
        unordered_map<long long, vector<float>> midPointMap;

        int result = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];

                int dx = x2 - x1;
                int dy = y2 - y1;

                float slope, intercept;

                if (dx == 0) {
                    slope = 1e9 + 7;       // vertical line
                    intercept = x1;        // x = constant
                } else {
                    slope = (float) dy / dx;
                    intercept = (float)(y1 * dx - x1 * dy) / dx;
                }

                // midpoint hashing key
                long long midKey = (long long)(x1 + x2) * 100000LL + (y1 + y2);

                slopeIntercepts[slope].push_back(intercept);
                midPointMap[midKey].push_back(slope);
            }
        }

        // Count pairs of parallel lines having different intercepts
        for (auto &it : slopeIntercepts) {
            if (it.second.size() <= 1) continue;

            map<float, int> mp;
            for (float b : it.second)
                mp[b]++;

            int prev = 0;
            for (auto &p : mp) {
                int cnt = p.second;
                result += cnt * prev;
                prev += cnt;
            }
        }

        // Subtract pairs that share the same midpoint → same segment
        for (auto &it : midPointMap) {
            if (it.second.size() <= 1) continue;

            map<float, int> mp;
            for (float s : it.second)
                mp[s]++;

            int prev = 0;
            for (auto &p : mp) {
                int cnt = p.second;
                result -= cnt * prev;
                prev += cnt;
            }
        }

        return result;
    }
};
