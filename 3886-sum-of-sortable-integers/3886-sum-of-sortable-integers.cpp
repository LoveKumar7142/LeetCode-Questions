
class Solution {
private:
    bool isSortable(vector<int>& nums, int k) {
        int n = nums.size();
        int previousMax = -1;

        for (int i = 0; i < n; i += k) {
            int mn = INT_MAX;
            int mx = INT_MIN;
            int drops = 0;

            for (int j = i; j < i + k; j++) {
                mn = min(mn, nums[j]);
                mx = max(mx, nums[j]);

                int next = i + (j - i + 1) % k;

                if (nums[j] > nums[next]) {
                    drops++;
                }

                if (drops > 1) return false;
            }

            if (i > 0 && previousMax > mn) {
                return false;
            }

            previousMax = mx;
        }

        return true;
    }

public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            if (isSortable(nums, k)) {
                ans += k;
            }
        }

        return ans;
    }
};
