class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(sum < 1 || sum > 9 * num) return "";

        string answer = "";

        while(num!= 0){
            int digit = min(9,sum);

            answer += char('0' + digit);

            sum -= digit;
            num--;
        }
        return answer;
    }
};