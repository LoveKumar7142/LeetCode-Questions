class Solution {
    struct Fenwick {
        int n;
        vector<int> bit;

        explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}

        void add(int index, int value) {
            for (++index; index <= n; index += index & -index) {
                bit[index] ^= value;
            }
        }

        void rangeXor(int left, int right, int value) {
            add(left, value);
            if (right + 1 < n) {
                add(right + 1, value);
            }
        }

        int pointQuery(int index) {
            int result = 0;
            for (++index; index > 0; index -= index & -index) {
                result ^= bit[index];
            }
            return result;
        }
    };

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n, 0));
        vector<int> depth(n), tin(n), tout(n);
        vector<int> initialPrefix(n), mask(n);

        for (int u = 0; u < n; ++u) {
            mask[u] = 1 << (s[u] - 'a');
        }

        // Iterative DFS avoids stack overflow on a long chain.
        vector<int> nextEdge(n, 0);
        vector<int> stack = {0};
        int timer = 0;

        tin[0] = timer++;
        initialPrefix[0] = mask[0];

        while (!stack.empty()) {
            int u = stack.back();

            if (nextEdge[u] == (int)graph[u].size()) {
                tout[u] = timer - 1;
                stack.pop_back();
                continue;
            }

            int v = graph[u][nextEdge[u]++];
            if (v == up[0][u]) continue;

            up[0][v] = u;
            depth[v] = depth[u] + 1;
            initialPrefix[v] = initialPrefix[u] ^ mask[v];
            tin[v] = timer++;
            stack.push_back(v);
        }

        for (int k = 1; k < LOG; ++k) {
            for (int u = 0; u < n; ++u) {
                up[k][u] = up[k - 1][up[k - 1][u]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int difference = depth[u] - depth[v];
            for (int k = 0; k < LOG; ++k) {
                if (difference & (1 << k)) {
                    u = up[k][u];
                }
            }

            if (u == v) return u;

            for (int k = LOG - 1; k >= 0; --k) {
                if (up[k][u] != up[k][v]) {
                    u = up[k][u];
                    v = up[k][v];
                }
            }

            return up[0][u];
        };

        Fenwick fenwick(n);
        vector<bool> answer;

        for (const string& query : queries) {
            istringstream input(query);
            string operation;
            int u;
            input >> operation >> u;

            if (operation == "update") {
                char c;
                input >> c;

                int newMask = 1 << (c - 'a');
                int delta = mask[u] ^ newMask;

                fenwick.rangeXor(tin[u], tout[u], delta);
                mask[u] = newMask;
            } else {
                int v;
                input >> v;

                int w = lca(u, v);
                int prefixU =
                    initialPrefix[u] ^ fenwick.pointQuery(tin[u]);
                int prefixV =
                    initialPrefix[v] ^ fenwick.pointQuery(tin[v]);

                int pathMask = prefixU ^ prefixV ^ mask[w];

                // True exactly when there are zero or one set bits.
                answer.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return answer;
    }
};