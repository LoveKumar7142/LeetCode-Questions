class Solution {
public:

    bool isValid(string s) {
        int balance = 0;

        for(char ch : s) {

            if(ch == '(') {
                balance++;
            }

            else if(ch == ')') {

                if(balance == 0)
                    return false;

                balance--;
            }
        }

        return balance == 0;
    }


    vector<string> removeInvalidParentheses(string s) {

        vector<string> ans;

        queue<string> q;
        unordered_set<string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;


        while(!q.empty()) {

            int size = q.size();

            for(int i = 0; i < size; i++) {

                string curr = q.front();
                q.pop();


                // Check validity
                if(isValid(curr)) {
                    ans.push_back(curr);
                    found = true;
                }


                // Don't generate next level
                // if valid strings already found
                if(found)
                    continue;


                // Remove one parenthesis
                for(int j = 0; j < curr.size(); j++) {

                    // Ignore letters
                    if(curr[j] != '(' && curr[j] != ')')
                        continue;


                    string next =
                        curr.substr(0, j) +
                        curr.substr(j + 1);


                    if(visited.find(next) == visited.end()) {

                        visited.insert(next);
                        q.push(next);
                    }
                }
            }

            if(found)
                break;
        }


        return ans;
    }
};