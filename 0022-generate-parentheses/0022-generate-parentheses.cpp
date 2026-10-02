class Solution {
private:
    bool isValid(string &s) {
        int ind = 0;
        for (char ch : s) {
            if (ch == '(') {
                ind++;
            } else {
                ind--;
                if (ind < 0) return false;
            }
        }
        return ind == 0;
    }
    vector<string> result;
    void generate(int n,string &v){
        if(v.length() == 2*n){
            if(isValid(v)){
                result.push_back(v);
            }
            return;
        }
        v.push_back('(');
        generate(n,v);
        v.pop_back();
        v.push_back(')');
        generate(n,v);
        v.pop_back();
    }
public:
    vector<string> generateParenthesis(int n) {
        string v;
        generate(n,v);
        return result;
    }
};