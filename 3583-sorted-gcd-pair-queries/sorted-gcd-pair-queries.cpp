class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);
        for (int x : nums) freq[x]++;

        vector<long long> cnt(mx + 1, 0);

        // cnt[d] = numbers divisible by d
        for (int d = 1; d <= mx; d++) {
            for (int j = d; j <= mx; j += d)
                cnt[d] += freq[j];
        }

        vector<long long> exact(mx + 1, 0);

        // Inclusion-Exclusion
        for (int d = mx; d >= 1; d--) {
            long long c = cnt[d];
            exact[d] = c * (c - 1) / 2;
            for (int j = d * 2; j <= mx; j += d)
                exact[d] -= exact[j];
        }

        vector<long long> pref(mx + 1, 0);
        for (int i = 1; i <= mx; i++)
            pref[i] = pref[i - 1] + exact[i];

        vector<int> ans;
        ans.reserve(queries.size());

        for (long long q : queries) {
            int l = 1, r = mx;
            while (l < r) {
                int mid = (l + r) / 2;
                if (pref[mid] > q)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans.push_back(l);
        }

        return ans;
    }
};