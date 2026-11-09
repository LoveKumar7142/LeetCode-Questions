
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival,
                               vector<int>& load) {
        set<int> available;
        
        // {endTime, serverId}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        int n = arrival.size();

        for (int i = 0; i < n; i++) {

            // Free servers whose tasks are completed
            while (!busy.empty() &&
                   busy.top().first <= arrival[i]) {

                int serverId = busy.top().second;
                busy.pop();

                available.insert(serverId);
            }

            // All servers are busy
            if (available.empty()) {
                continue;
            }

            // Find server >= i % k
            auto it = available.lower_bound(i % k);

            // Wrap around
            if (it == available.end()) {
                it = available.begin();
            }

            int serverId = *it;
            available.erase(it);

            count[serverId]++;

            long long endTime =
                (long long)arrival[i] + load[i];

            busy.push({endTime, serverId});
        }

        int maxRequests =
            *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxRequests) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
