class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long int sum = 0;
        for(auto& num : nums){
            sum += (1LL * num*num);
        }
        for(int i = 0;i<nums.size();i++){
            if(nums[i] < 0) nums[i] = -nums[i];
        }
        sort(nums.begin(),nums.end());

        int len = nums.size()/2;
        for(int i =0;i<len;i++){
            sum -= (2LL*nums[i]*nums[i]);
        }
        return sum;
    }
};