class Solution {
public:
    int maxDepth(string s) {
        int cnt_open_close = 0,ans = 0;
        for(auto ch : s){
            if(ch == '(') ans = max(ans,++cnt_open_close);
            else if(ch == ')') cnt_open_close--;
        }
        return ans;
    }
};