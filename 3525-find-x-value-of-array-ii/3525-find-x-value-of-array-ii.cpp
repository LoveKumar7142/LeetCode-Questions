class Solution {
private:
    struct Node {
        int cnt[5] = {0, 0, 0, 0, 0};
        int prod = 1;
        bool empty = true;
    };

    int n, K;
    vector<Node> tree;

    Node mergeNode(const Node& left, const Node& right) {
        if (left.empty) return right;
        if (right.empty) return left;

        Node res;
        res.empty = false;

        res.prod = (left.prod * right.prod) % K;

        // Prefixes completely inside left
        for (int r = 0; r < K; r++) {
            res.cnt[r] += left.cnt[r];
        }

        // Whole left + prefix of right
        for (int r = 0; r < K; r++) {
            int newRem = (left.prod * r) % K;

            res.cnt[newRem] += right.cnt[r];
        }

        return res;
    }

    Node makeNode(int value) {
        Node node;

        node.empty = false;

        node.prod = value % K;

        node.cnt[node.prod] = 1;

        return node;
    }

    void build(
        int idx,
        int l,
        int r,
        vector<int>& nums
    ) {
        if (l == r) {
            tree[idx] = makeNode(nums[l]);
            return;
        }

        int mid = l + (r - l) / 2;

        build(idx * 2, l, mid, nums);

        build(
            idx * 2 + 1,
            mid + 1,
            r,
            nums
        );

        tree[idx] = mergeNode(
            tree[idx * 2],
            tree[idx * 2 + 1]
        );
    }

    void update(
        int idx,
        int l,
        int r,
        int pos,
        int value
    ) {
        if (l == r) {
            tree[idx] = makeNode(value);
            return;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            update(
                idx * 2,
                l,
                mid,
                pos,
                value
            );
        }
        else {
            update(
                idx * 2 + 1,
                mid + 1,
                r,
                pos,
                value
            );
        }

        tree[idx] = mergeNode(
            tree[idx * 2],
            tree[idx * 2 + 1]
        );
    }

    Node query(
        int idx,
        int l,
        int r,
        int ql,
        int qr
    ) {
        // No overlap
        if (r < ql || qr < l) {
            return Node();
        }

        // Complete overlap
        if (ql <= l && r <= qr) {
            return tree[idx];
        }

        int mid = l + (r - l) / 2;

        Node left = query(
            idx * 2,
            l,
            mid,
            ql,
            qr
        );

        Node right = query(
            idx * 2 + 1,
            mid + 1,
            r,
            ql,
            qr
        );

        return mergeNode(left, right);
    }

public:
    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        K = k;

        tree.resize(4 * n);

        build(
            1,
            0,
            n - 1,
            nums
        );

        vector<int> result;

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(
                1,
                0,
                n - 1,
                index,
                value
            );

            // Analyze nums[start ... n-1]
            Node current = query(
                1,
                0,
                n - 1,
                start,
                n - 1
            );

            result.push_back(
                current.cnt[x]
            );
        }

        return result;
    }
};