class Solution {
public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        vector<int> halfFreq(26, 0);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        auto countWays = [&](vector<int>& cnt) -> long long {
            long long ways = 1;
            int remaining = 0;

            for (int x : cnt) {
                remaining += x;
            }

            for (int c = 0; c < 26; c++) {
                int take = cnt[c];

                if (take == 0)
                    continue;

                for (int i = 1; i <= take; i++) {
                    ways = ways * (remaining - take + i) / i;

                    if (ways >= k) {
                        return k;
                    }
                }

                remaining -= take;
            }

            return ways;
        };

        if (countWays(halfFreq) < k) {
            return "";
        }

        string firstHalf = "";
        int halfLength = s.length() / 2;

        for (int pos = 0; pos < halfLength; pos++) {
            for (int c = 0; c < 26; c++) {

                if (halfFreq[c] == 0) {
                    continue;
                }

                halfFreq[c]--;

                long long ways = countWays(halfFreq);

                if (k > ways) {
                    k -= ways;
                    halfFreq[c]++;
                }
                else {
                    firstHalf += char('a' + c);
                    break;
                }
            }
        }

        string middle = "";

        if (s.length() % 2 == 1) {
            for (int i = 0; i < 26; i++) {
                if (freq[i] % 2 == 1) {
                    middle += char('a' + i);
                    break;
                }
            }
        }

        string secondHalf = firstHalf;
        reverse(secondHalf.begin(), secondHalf.end());

        return firstHalf + middle + secondHalf;
    }
};

