class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int len = m + n - 1;

        // Valid parentheses string must have even length
        if (len % 2 == 1)
            return false;

        // Must start with '(' and end with ')'
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(')
            return false;

        vector<vector<vector<bool>>> dp(
            m,
            vector<vector<bool>>(
                n,
                vector<bool>(len + 1, false)
            )
        );

        dp[0][0][1] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int bal = 0; bal <= len; bal++) {

                    bool reachable = false;

                    // Coming from top
                    if (i > 0 && dp[i - 1][j][bal])
                        reachable = true;

                    // Coming from left
                    if (j > 0 && dp[i][j - 1][bal])
                        reachable = true;

                    if (!reachable)
                        continue;

                    if (grid[i][j] == '(') {
                        if (bal + 1 <= len)
                            dp[i][j][bal + 1] = true;
                    }
                    else {
                        if (bal > 0)
                            dp[i][j][bal - 1] = true;
                    }
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};