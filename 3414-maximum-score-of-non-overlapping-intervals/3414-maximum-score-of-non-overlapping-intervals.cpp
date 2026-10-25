class Solution {
    struct State {
        long long score = 0;
        vector<int> indices;
    };

    State better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score ? a : b;
        return a.indices < b.indices ? a : b;
    }

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<int, 4>> items;
        for (int i = 0; i < n; ++i) {
            items.push_back({
                intervals[i][0], intervals[i][1], intervals[i][2], i
            });
        }
        sort(items.begin(), items.end());

        vector<int> starts(n), nextIndex(n);
        for (int i = 0; i < n; ++i)
            starts[i] = items[i][0];

        for (int i = 0; i < n; ++i) {
            // Start must be strictly greater than the current end.
            nextIndex[i] = upper_bound(
                starts.begin(), starts.end(), items[i][1]
            ) - starts.begin();
        }

        vector<State> previous(n + 1);

        for (int k = 1; k <= 4; ++k) {
            vector<State> current(n + 1);

            for (int i = n - 1; i >= 0; --i) {
                State take = previous[nextIndex[i]];
                take.score += items[i][2];
                take.indices.push_back(items[i][3]);
                sort(take.indices.begin(), take.indices.end());

                current[i] = better(take, current[i + 1]);
            }

            previous.swap(current);
        }

        return previous[0].indices;
    }
};