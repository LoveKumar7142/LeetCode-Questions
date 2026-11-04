
class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        // Balance both halves of the sliding window
        auto balance = [&]() {
            while (low.size() > high.size() + 1) {
                int val = *low.rbegin();
                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while (low.size() < high.size()) {
                int val = *high.begin();
                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        // cost[i] = cost of window ending at position i
        // (1-based positions)
        vector<long long> cost(n + 1, 0);

        for (int i = 0; i < n; i++) {
            int val = nums[i];

            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            balance();

            // Remove element outside the window
            if (i >= x) {
                int out = nums[i - x];

                auto it = low.find(out);

                if (it != low.end()) {
                    low.erase(it);
                    sumLow -= out;
                } else {
                    high.erase(high.find(out));
                    sumHigh -= out;
                }

                balance();
            }

            // Calculate minimum cost using median
            if (i >= x - 1) {
                long long median = *low.rbegin();

                cost[i + 1] =
                    median * low.size() - sumLow
                    + sumHigh - median * high.size();
            }
        }

        // DP: select exactly k non-overlapping windows
        const long long INF = LLONG_MAX / 4;

        vector<long long> previous(n + 1, 0);
        vector<long long> current(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(current.begin(), current.end(), INF);

            for (int i = 1; i <= n; i++) {
                // Skip current position
                current[i] = current[i - 1];

                // Select window ending at i
                if (i >= x && previous[i - x] != INF) {
                    current[i] = min(
                        current[i],
                        previous[i - x] + cost[i]
                    );
                }
            }

            swap(previous, current);
        }

        return previous[n];
    }
};
