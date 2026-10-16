
class Solution {
    static constexpr long long MOD = 1000000007LL;

    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;

        tree[node].sq = (
            tree[node].sq
            + 2LL * val * tree[node].sum
            + val * val % MOD * len
        ) % MOD;

        tree[node].sum = (
            tree[node].sum + val * len
        ) % MOD;

        tree[node].lazy += val;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r)
            return;

        int mid = l + (r - l) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r,
                int ql, int qr) {
        if (qr < l || r < ql) return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);

        int mid = l + (r - l) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        tree[node].sum = (
            tree[node * 2].sum
            + tree[node * 2 + 1].sum
        ) % MOD;

        tree[node].sq = (
            tree[node * 2].sq
            + tree[node * 2 + 1].sq
        ) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        tree.assign(4 * n + 5, Node{});

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int p = last[nums[r]];
            update(1, 0, n - 1, p + 1, r);

            ans = (ans + tree[1].sq) % MOD;

            last[nums[r]] = r;
        }

        return (int)ans;
    }
};
