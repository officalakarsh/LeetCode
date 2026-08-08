class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // last[j] = position in word1 where word2[j] can be matched
        // while still allowing word2[j+1 ...] to be matched.
        vector<int> last(m, -1);

        int i = n - 1;
        int j = m - 1;

        // Match word2 from right to left.
        while (i >= 0 && j >= 0) {
            if (word1[i] == word2[j]) {
                last[j] = i;
                j--;
            }
            i--;
        }

        vector<int> ans;
        ans.reserve(m);

        bool usedMismatch = false;
        j = 0;

        // Greedily scan word1 from left to right.
        for (i = 0; i < n && j < m; i++) {

            // Perfect match: always take it.
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            }

            // Use the one allowed mismatch.
            else if (!usedMismatch) {

                // If this is the last character, we can always
                // use the mismatch.
                //
                // Otherwise, word2[j+1] must still be matchable
                // after index i.
                if (j == m - 1 || 
                    (last[j + 1] != -1 && i < last[j + 1])) {

                    ans.push_back(i);
                    j++;
                    usedMismatch = true;
                }
            }
        }

        // Couldn't construct a sequence of length word2.length().
        if (j != m)
            return {};

        return ans;
    }
};