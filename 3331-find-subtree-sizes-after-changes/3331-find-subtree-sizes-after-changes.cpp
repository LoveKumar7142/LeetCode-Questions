
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        // DFS on the original tree
        auto dfs = [&](auto&& self, int node) -> void {
            int c = s[node] - 'a';

            if (last[c] != -1) {
                newParent[node] = last[c];
            }

            int previous = last[c];
            last[c] = node;

            for (int child : adj[node]) {
                self(self, child);
            }

            last[c] = previous;
        };

        dfs(dfs, 0);

        // Build the modified tree
        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        vector<int> answer(n, 1);

        auto dfs2 = [&](auto&& self, int node) -> void {
            for (int child : newAdj[node]) {
                self(self, child);
                answer[node] += answer[child];
            }
        };

        dfs2(dfs2, 0);

        return answer;
    }
};
