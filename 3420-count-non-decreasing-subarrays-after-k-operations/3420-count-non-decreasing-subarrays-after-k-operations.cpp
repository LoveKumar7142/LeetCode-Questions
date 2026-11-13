
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<pair<long long, int>> dq;

        long long cost = 0;
        long long ans = 0;

        int right = n - 1;

        for (int left = n - 1; left >= 0; left--) {

            long long value = nums[left];
            int count = 1;

            while (!dq.empty() && dq.front().first <= value) {
                auto [val, freq] = dq.front();
                dq.pop_front();

                cost += (value - val) * freq;
                count += freq;
            }

            dq.push_front({value, count});

            while (cost > k) {
                auto& [val, freq] = dq.back();

                cost -= val - nums[right];

                freq--;

                if (freq == 0) {
                    dq.pop_back();
                }

                right--;
            }

            ans += right - left + 1;
        }

        return ans;
    }
};