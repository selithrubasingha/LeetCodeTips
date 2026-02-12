## Climbing Stairs

- You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Subproblem :** If I know the distict ways to reach the 4th stair , AND the ways to reach the 3rd floor , I can easily find the answer for 5th floor casue it's

    5th = 4th + 3rd

```C++
#include <vector>

class Solution {
public:
    int climbStairs(int n) {
        // Create a memoization table (cache) initialized with -1
        // Size is n + 1 because we need index 'n'
        std::vector<int> memo(n + 1, -1);
        
        return solve(n, memo);
    }

private:
    int solve(int n, std::vector<int>& memo) {
        // Base cases
        if (n == 1) return 1;
        if (n == 2) return 2;

        // CHECK THE CACHE: If we already calculated this, return it!
        if (memo[n] != -1) {
            return memo[n];
        }

        // STORE THE RESULT: Calculate once, save it in 'memo'
        memo[n] = solve(n - 1, memo) + solve(n - 2, memo);
        
        return memo[n];
    }
};
```