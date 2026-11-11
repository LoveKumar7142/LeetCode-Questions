
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth,
                          int need1, int need2) {

        long long common = min(need1, need2);
        long long extra = max(need1, need2) - common;

        long long commonCost = common * 
                              min(1LL * costBoth, 1LL * cost1 + cost2);

        long long extraCost;

        if (need1 > need2) {
            extraCost = extra * min(cost1, costBoth);
        } else {
            extraCost = extra * min(cost2, costBoth);
        }

        return commonCost + extraCost;
    }
};
