class Solution {
public:
    string smallestNumber(string num, long long t) {
        int need[4] = {0, 0, 0, 0};
        int primes[4] = {2, 3, 5, 7};

        for (int i = 0; i < 4; i++) {
            while (t % primes[i] == 0) {
                need[i]++;
                t /= primes[i];
            }
        }

        if (t != 1)
            return "-1";

        int A = need[0] + 1;
        int B = need[1] + 1;
        int C = need[2] + 1;
        int D = need[3] + 1;

        int total = A * B * C * D;

        auto id = [&](int a, int b, int c, int d) {
            return ((a * B + b) * C + c) * D + d;
        };

        const unsigned char INF = 255;

        vector<unsigned char> dp(total, INF);
        dp[id(0, 0, 0, 0)] = 0;

        int fac[10][4] = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {2, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 1},
            {3, 0, 0, 0},
            {0, 2, 0, 0}
        };

        // dp[state] = minimum number of digits needed
        // to satisfy the required prime exponents of this state.
        for (int a = 0; a <= need[0]; a++) {
            for (int b = 0; b <= need[1]; b++) {
                for (int c = 0; c <= need[2]; c++) {
                    for (int d = 0; d <= need[3]; d++) {
                        if (a == 0 && b == 0 && c == 0 && d == 0)
                            continue;

                        int best = 1000000;

                        for (int x = 2; x <= 9; x++) {
                            int pa = max(0, a - fac[x][0]);
                            int pb = max(0, b - fac[x][1]);
                            int pc = max(0, c - fac[x][2]);
                            int pd = max(0, d - fac[x][3]);

                            int prev = dp[id(pa, pb, pc, pd)];

                            if (prev != INF)
                                best = min(best, prev + 1);
                        }

                        dp[id(a, b, c, d)] = best;
                    }
                }
            }
        }

        auto getMinDigits = [&](int r2, int r3, int r5, int r7) {
            return (int)dp[id(r2, r3, r5, r7)];
        };

        int n = num.size();

        // Prefix prime-factor counts.
        vector<array<int, 4>> pref(n + 1);

        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i];

            int x = num[i] - '0';

            if (x >= 1) {
                for (int j = 0; j < 4; j++) {
                    pref[i + 1][j] = min(
                        need[j],
                        pref[i + 1][j] + fac[x][j]
                    );
                }
            }
        }

        // Check whether num itself works.
        bool zeroFree = true;

        for (char ch : num) {
            if (ch == '0') {
                zeroFree = false;
                break;
            }
        }

        if (zeroFree) {
            bool ok = true;

            for (int j = 0; j < 4; j++) {
                if (pref[n][j] < need[j]) {
                    ok = false;
                    break;
                }
            }

            if (ok)
                return num;
        }

        // Find the rightmost position where we can increase
        // the digit and still make a valid number.
        int firstZero = n;

        for (int i = 0; i < n; i++) {
            if (num[i] == '0') {
                firstZero = i;
                break;
            }
        }

        for (int pos = n - 1; pos >= 0; pos--) {
            // If there is a zero before pos, the equal prefix
            // would contain zero, so this position cannot be used.
            if (pos > firstZero)
                continue;

            int current = num[pos] - '0';

            for (int digit = current + 1; digit <= 9; digit++) {
                int have[4];

                for (int j = 0; j < 4; j++) {
                    have[j] = min(
                        need[j],
                        pref[pos][j] + fac[digit][j]
                    );
                }

                int r2 = need[0] - have[0];
                int r3 = need[1] - have[1];
                int r5 = need[2] - have[2];
                int r7 = need[3] - have[3];

                int remaining = n - pos - 1;

                if (getMinDigits(r2, r3, r5, r7) <= remaining) {
                    string ans = num.substr(0, pos);
                    ans.push_back(char('0' + digit));

                    // Construct lexicographically smallest suffix.
                    for (int i = 0; i < remaining; i++) {
                        int left = remaining - i - 1;

                        for (int d = 1; d <= 9; d++) {
                            int nhave[4];

                            for (int j = 0; j < 4; j++) {
                                nhave[j] = min(
                                    need[j],
                                    have[j] + fac[d][j]
                                );
                            }

                            int nr2 = need[0] - nhave[0];
                            int nr3 = need[1] - nhave[1];
                            int nr5 = need[2] - nhave[2];
                            int nr7 = need[3] - nhave[3];

                            if (getMinDigits(nr2, nr3, nr5, nr7) <= left) {
                                ans.push_back(char('0' + d));

                                for (int j = 0; j < 4; j++)
                                    have[j] = nhave[j];

                                break;
                            }
                        }
                    }

                    return ans;
                }
            }
        }

        // No answer of the same length.
        // Find the minimum length that can contain all factors.
        int minLen = getMinDigits(
            need[0],
            need[1],
            need[2],
            need[3]
        );

        int len = max(n + 1, minLen);

        string ans;

        int have[4] = {0, 0, 0, 0};

        for (int i = 0; i < len; i++) {
            int left = len - i - 1;

            for (int d = 1; d <= 9; d++) {
                int nhave[4];

                for (int j = 0; j < 4; j++) {
                    nhave[j] = min(
                        need[j],
                        have[j] + fac[d][j]
                    );
                }

                int r2 = need[0] - nhave[0];
                int r3 = need[1] - nhave[1];
                int r5 = need[2] - nhave[2];
                int r7 = need[3] - nhave[3];

                if (getMinDigits(r2, r3, r5, r7) <= left) {
                    ans.push_back(char('0' + d));

                    for (int j = 0; j < 4; j++)
                        have[j] = nhave[j];

                    break;
                }
            }
        }

        return ans;
    }
};