class Solution {
public:
    string s;
    int i = 0;

    set<string> mergeSet(set<string>& a, set<string>& b) {
        set<string> result = a;

        for (auto& word : b) {
            result.insert(word);
        }

        return result;
    }

    set<string> multiply(set<string>& a, set<string>& b) {
        set<string> result;

        for (auto& x : a) {
            for (auto& y : b) {
                result.insert(x + y);
            }
        }

        return result;
    }

    set<string> parse() {
        // result -> handles union
        set<string> result;

        // current -> handles concatenation
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union:
                // save everything we built before comma
                result = mergeSet(result, current);

                // start a new expression after comma
                current = {""};

                i++;
            }
            else {
                set<string> next;

                if (s[i] == '{') {
                    i++; // skip '{'

                    next = parse();

                    i++; // skip '}'
                }
                else {
                    // single character
                    next.insert(string(1, s[i]));
                    i++;
                }

                // Adjacent expressions mean concatenation
                current = multiply(current, next);
            }
        }

        // Add last part
        result = mergeSet(result, current);

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        s = expression;

        set<string> words = parse();

        return vector<string>(words.begin(), words.end());
    }
};