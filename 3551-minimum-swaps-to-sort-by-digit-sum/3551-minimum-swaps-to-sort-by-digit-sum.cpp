
class Solution {
private:
    int digitSum(int num) {
        int sum = 0;

        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }

public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<int> sorted = nums;

        // Step 1: Sort by digit sum, then by value
        sort(sorted.begin(), sorted.end(),
             [&](int a, int b) {
                 int sumA = digitSum(a);
                 int sumB = digitSum(b);

                 if (sumA == sumB)
                     return a < b;

                 return sumA < sumB;
             });

        // Step 2: Map each number to its target index
        unordered_map<int, int> target;

        for (int i = 0; i < n; i++) {
            target[sorted[i]] = i;
        }

        // Step 3: Count swaps using cycle detection
        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;

            int current = i;
            int cycleSize = 0;

            while (!visited[current]) {
                visited[current] = true;
                current = target[nums[current]];
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += cycleSize - 1;
            }
        }

        return swaps;
    }
};
