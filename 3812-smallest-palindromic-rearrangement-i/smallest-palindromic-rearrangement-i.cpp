class Solution {
public:
    string smallestPalindrome(string s) {
        // Count frequency of each character
        int freq[26] = {0};

        for (char ch : s) {
            freq[ch - 'a']++;
        }

        string left = "";

        // Build the left half in lexicographically smallest order
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < freq[i] / 2; j++) {
                left += char('a' + i);
            }
        }

        // Find the middle character (only for odd length)
        string middle = "";

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 != 0) {
                middle = char('a' + i);
                break;
            }
        }

        // Right half is reverse of left half
        string right = left;
        reverse(right.begin(), right.end());

        return left + middle + right;
    }
};