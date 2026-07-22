class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(
        string s,
        vector<vector<int>>& queries
    ) {
        int n = s.size();

        // --------------------------------------------------
        // a contains all zero-runs as [left, right)
        //
        // Sentinels:
        // a[0] = {-1, -1}
        // a.back() = {n + 1, n + 1}
        // --------------------------------------------------
        vector<pair<int, int>> a;
        a.push_back({-1, -1});

        // belong[i] tells us which zero-run is immediately
        // to the right of position i.
        vector<int> belong(n);

        int total1 = 0;
        int start = 0;

        for (int i = 0; i < n; i++) {

            belong[i] = (int)a.size();

            if (i == n - 1 || s[i] != s[i + 1]) {

                if (s[i] == '1') {

                    // Count total number of 1s
                    total1 += i - start + 1;

                } else {

                    // Store zero-run as [start, i + 1)
                    a.push_back({start, i + 1});
                }

                start = i + 1;
            }
        }

        a.push_back({n + 1, n + 1});

        int m = a.size();

        // --------------------------------------------------
        // For every pair of adjacent zero-runs:
        //
        // 000 | 111 | 00
        //
        // If we trade the 111 block, the two zero-runs
        // are merged and converted to 1s.
        //
        // The gain is:
        //
        // length(left zero-run)
        // +
        // length(right zero-run)
        //
        // --------------------------------------------------

        vector<int> value(m - 1, 0);

        for (int i = 0; i + 1 < m; i++) {

            int leftZero =
                a[i].second - a[i].first;

            int rightZero =
                a[i + 1].second - a[i + 1].first;

            if (leftZero > 0 && rightZero > 0) {
                value[i] =
                    leftZero + rightZero;
            }
        }

        // --------------------------------------------------
        // Sparse Table
        // --------------------------------------------------

        int LOG = 20;

        vector<vector<int>> st(
            LOG,
            vector<int>(m - 1, 0)
        );

        for (int i = 0; i < m - 1; i++) {
            st[0][i] = value[i];
        }

        for (int k = 1; k < LOG; k++) {

            for (int i = 0;
                 i + (1 << k) <= m - 1;
                 i++) {

                st[k][i] = max(
                    st[k - 1][i],
                    st[k - 1][
                        i + (1 << (k - 1))
                    ]
                );
            }
        }

        auto rangeMax = [&](int l, int r) {

            // Query [l, r)
            if (l >= r)
                return 0;

            int len = r - l;

            int k =
                31 - __builtin_clz(len);

            return max(
                st[k][l],
                st[k][
                    r - (1 << k)
                ]
            );
        };

        // --------------------------------------------------
        // Merge helper
        //
        // Both x and y must be positive.
        // --------------------------------------------------

        auto merge = [&](int x, int y) {

            if (x > 0 && y > 0)
                return x + y;

            return 0;
        };

        vector<int> answer;

        // --------------------------------------------------
        // Process queries
        // --------------------------------------------------

        for (auto &query : queries) {

            int ql = query[0];
            int qr = query[1];

            // Find zero-run immediately to the right of ql
            int i = belong[ql];

            // If ql is inside a zero-run that started before
            // the query, move to the next zero-run.
            if (ql > 0 &&
                s[ql] == '0' &&
                s[ql - 1] == '0') {

                i++;
            }

            // Find zero-run immediately to the right of qr
            int j = belong[qr] - 1;

            // If qr is the last zero of a zero-run and the
            // next character is 1, adjust the index.
            if (qr + 1 < n &&
                s[qr] == '0' &&
                s[qr + 1] == '1') {

                j++;
            }

            // Make qr exclusive
            int right = qr + 1;

            int bestGain = 0;

            if (i <= j) {

                // Best complete pair of zero-runs
                bestGain = max(
                    bestGain,
                    rangeMax(i, j)
                );

                // Candidate involving the left boundary
                bestGain = max(
                    bestGain,
                    merge(
                        a[i - 1].second - ql,
                        a[i].second - a[i].first
                    )
                );

                // Candidate involving the right boundary
                bestGain = max(
                    bestGain,
                    merge(
                        right - a[j + 1].first,
                        a[j].second - a[j].first
                    )
                );

            } else if (i == j + 1) {

                // There is no complete zero-run between
                // the query boundaries.
                //
                // We may still have:
                //
                // partial zero on left
                // +
                // partial zero on right
                //
                bestGain = merge(
                    a[i - 1].second - ql,
                    right - a[j + 1].first
                );
            }

            // Original number of 1s + maximum additional 1s
            answer.push_back(
                total1 + bestGain
            );
        }

        return answer;
    }
};