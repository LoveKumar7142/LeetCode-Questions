
class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();

        // dp[i][j][0] = paths arriving from left (moving right)
        // dp[i][j][1] = paths arriving from top (moving down)
        vector<vector<array<int, 2>>> dp(
            m, vector<array<int, 2>>(n, {0, 0})
        );

        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                long long right = 0, down = 0;

                // Entering from left
                if (j > 0) {
                    if (grid[i][j - 1] == 0)
                        right = (dp[i][j - 1][0] +
                                 dp[i][j - 1][1]) % MOD;
                    else
                        right = dp[i][j - 1][1];
                }

                // Entering from top
                if (i > 0) {
                    if (grid[i - 1][j] == 0)
                        down = (dp[i - 1][j][0] +
                                dp[i - 1][j][1]) % MOD;
                    else
                        down = dp[i - 1][j][0];
                }

                dp[i][j][0] = right;
                dp[i][j][1] = down;
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};
