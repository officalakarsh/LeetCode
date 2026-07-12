class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> temp = arr;
        sort(temp.begin(), temp.end());

        unordered_map<int, int> rank;
        int r = 1;

        for (int x : temp) {
            if (!rank.count(x)) {
                rank[x] = r++;
            }
        }

        vector<int> ans;
        for (int x : arr) {
            ans.push_back(rank[x]);
        }

        return ans;
    }
};