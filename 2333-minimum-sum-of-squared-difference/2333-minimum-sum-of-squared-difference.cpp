
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1,
                                vector<int>& nums2,
                                int k1, int k2) {
        int n = nums1.size();
        vector<int> diff(n);

        long long k = (long long)k1 + k2;
        long long totalDiff = 0;
        int maxDiff = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            totalDiff += diff[i];
            maxDiff = max(maxDiff, diff[i]);
        }

        if (totalDiff <= k) return 0;

        int low = 0, high = maxDiff;

        while (low < high) {
            int mid = low + (high - low) / 2;

            long long operations = 0;

            for (int d : diff) {
                if (d > mid) {
                    operations += d - mid;
                }
            }

            if (operations <= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        long long remaining = k;

        for (int& d : diff) {
            if (d > low) {
                remaining -= d - low;
                d = low;
            }
        }

        // Use remaining operations on differences == low
        long long ans = 0;

        for (int d : diff) {
            if (d == low && remaining > 0) {
                d--;
                remaining--;
            }

            ans += 1LL * d * d;
        }

        return ans;
    }
};
