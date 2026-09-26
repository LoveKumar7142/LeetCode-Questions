class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key -> value
        for (auto &item : knowledge) {
            mp[item[0]] = item[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {

            // Normal character
            if (s[i] != '(') {
                ans += s[i];
            }
            else {
                // Extract key inside brackets
                string key;
                i++;  // skip '('

                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                if (mp.count(key)) {
                    ans += mp[key];
                }
                else {
                    ans += '?';
                }
            }
        }

        return ans;
    }
};