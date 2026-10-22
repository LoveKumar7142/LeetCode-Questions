
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int pos = 0;

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                pos = i;
                break;
            }
        }

        bool ascending = true;
        bool descending = true;

        for (int i = 0; i < n; i++) {
            int value = nums[(pos + i) % n];

            if (value != i)
                ascending = false;

            if (value != (n - i) % n)
                descending = false;
        }

        int ans = INT_MAX;

        if (ascending) {
            ans = min(ans, min(pos, n - pos + 2));
        }

        if (descending) {
            ans = min(ans, min(n - pos, pos + 2));
        }

        return ans == INT_MAX ? -1 : ans;
    }
};
