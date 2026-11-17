
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Step 1: Precompute minimum changes for each substring
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;

                // Try every valid divisor
                for (int d = 1; d < len; d++) {
                    if (len % d != 0) continue;

                    int changes = 0;

                    for (int start = 0; start < d; start++) {
                        int left = i + start;
                        int right = i + start + (len / d - 1) * d;

                        while (left < right) {
                            if (s[left] != s[right]) {
                                changes++;
                            }

                            left += d;
                            right -= d;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // Step 2: Partition DP
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));

        dp[0][0] = 0;

        for (int part = 1; part <= k; part++) {
            for (int end = 2 * part; end <= n; end++) {
                for (int start = 2 * (part - 1);
                     start <= end - 2; start++) {

                    if (dp[part - 1][start] == INF) continue;

                    dp[part][end] = min(
                        dp[part][end],
                        dp[part - 1][start] + cost[start][end - 1]
                    );
                }
            }
        }

        return dp[k][n];
    }
};
