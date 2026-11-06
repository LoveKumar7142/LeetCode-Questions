
class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs,
                             int x, vector<int>& queries) {

        sort(logs.begin(), logs.end(),
             [](const auto& a, const auto& b) {
                 return a[1] < b[1];
             });

        vector<pair<int, int>> q;
        for (int i = 0; i < queries.size(); i++) {
            q.push_back({queries[i], i});
        }

        sort(q.begin(), q.end());

        vector<int> ans(queries.size());
        vector<int> freq(n + 1, 0);

        int left = 0, right = 0;
        int active = 0;

        for (auto [time, index] : q) {

            // Add logs with timestamp <= query time
            while (right < logs.size() && logs[right][1] <= time) {
                int id = logs[right][0];

                if (freq[id] == 0) active++;

                freq[id]++;
                right++;
            }

            // Remove logs older than query time - x
            while (left < right && logs[left][1] < time - x) {
                int id = logs[left][0];

                freq[id]--;

                if (freq[id] == 0) active--;

                left++;
            }

            ans[index] = n - active;
        }

        return ans;
    }
};
