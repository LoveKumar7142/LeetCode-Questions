
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        long long moves = 0;

        for (int num : nums) {
            moves += (long long)num - mn;
        }

        return (int)moves;
    }
};
