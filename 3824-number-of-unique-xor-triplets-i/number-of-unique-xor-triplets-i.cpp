class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        // For n = 1 or 2, only the values 1...n can be obtained.
        if (n < 3)
            return n;

        // Find the smallest power of 2 greater than n.
        int p = 1;
        while (p <= n)
            p *= 2;

        // All values from 0 to p-1 are possible.
        return p;
    }
};