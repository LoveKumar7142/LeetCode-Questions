class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long int sum = 0;
        for(auto& num : nums){
            sum += (1LL * num*num);
            if(num < 0) num = -num;
        }
        int len = nums.size()/2;

        if(len > 0)
            nth_element(nums.begin(),nums.begin()+len,nums.end());

        for(int i =0;i<len;i++)
            sum -= (2LL*nums[i]*nums[i]);
        return sum;
    }
};