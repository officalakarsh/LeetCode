class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();

        // Count original number of 1s
        int originalOnes = 0;

        for (char c : s) {
            if (c == '1') {
                originalOnes++;
            }
        }

        int answer = originalOnes;

        // Add virtual 1s at both ends
        string t = "1" + s + "1";

        // Run-length encoding
        vector<int> len;
        vector<char> type;

        for (int i = 0; i < t.size(); ) {
            int j = i;

            while (j < t.size() && t[j] == t[i]) {
                j++;
            }

            type.push_back(t[i]);
            len.push_back(j - i);

            i = j;
        }

        /*
            We look for:

                0-block | 1-block | 0-block

            Example:

                00 | 1 | 000

            First:
                00 | 00000

            Then:
                11 | 11111

            The number of 1s becomes:

            originalOnes
            - length of selected 1-block
            + length of left 0-block
            + length of selected 1-block
            + length of right 0-block

            The selected 1-block cancels out.

            Therefore:

            newOnes = originalOnes
                      + leftZero
                      + rightZero
        */

        for (int i = 1; i + 1 < len.size(); i++) {

            if (type[i] == '1' &&
                type[i - 1] == '0' &&
                type[i + 1] == '0') {

                int leftZero = len[i - 1];
                int rightZero = len[i + 1];

                int candidate =
                    originalOnes + leftZero + rightZero;

                answer = max(answer, candidate);
            }
        }

        return answer;
    }
};