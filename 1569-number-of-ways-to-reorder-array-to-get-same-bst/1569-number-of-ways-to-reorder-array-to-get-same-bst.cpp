
class Solution {
private:
    static constexpr long long MOD = 1000000007LL;

    vector<vector<long long>> combination;

    long long solve(const vector<int>& nums) {
        int n = nums.size();

        if (n <= 2) return 1;

        vector<int> left, right;

        int root = nums[0];

        for (int i = 1; i < n; i++) {
            if (nums[i] < root) {
                left.push_back(nums[i]);
            } else {
                right.push_back(nums[i]);
            }
        }

        long long leftWays = solve(left);
        long long rightWays = solve(right);

        long long interleave =
            combination[n - 1][left.size()];

        return ((interleave * leftWays) % MOD
                * rightWays) % MOD;
    }

public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();

        combination.assign(
            n + 1, vector<long long>(n + 1, 0)
        );

        // Pascal's Triangle: nCr
        for (int i = 0; i <= n; i++) {
            combination[i][0] = 1;
            combination[i][i] = 1;

            for (int j = 1; j < i; j++) {
                combination[i][j] =
                    (combination[i - 1][j - 1] +
                     combination[i - 1][j]) % MOD;
            }
        }

        return (solve(nums) - 1 + MOD) % MOD;
    }
};
