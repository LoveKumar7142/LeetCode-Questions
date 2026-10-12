
class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        int count[30] = {0};

        // Step 1: Count set bits
        for (int num : nums) {
            for (int bit = 0; bit < 30; bit++) {
                if (num & (1 << bit)) {
                    count[bit]++;
                }
            }
        }

        long long ans = 0;

        // Step 2: Construct k maximum numbers
        for (int i = 0; i < k; i++) {
            long long num = 0;

            for (int bit = 0; bit < 30; bit++) {
                if (count[bit] > 0) {
                    num |= (1LL << bit);
                    count[bit]--;
                }
            }
            ans = (ans + num * num) % MOD;
        }

        return (int)ans;
    }
};
