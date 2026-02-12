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

## Min Cost Climbing Stairs

- You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.You can either start from the step with index 0, or the step with index 1.Return the minimum cost to reach the top of the floor.

**Subproblem:**
    This is super similar to the climbing stairs problem . The difference is that it has a cost now .

So if i am in the fifth floor , I could climb to it from teh 4th or 3rd floors , but I need to choose the one with the minimum cost , so the recursive answer is the minimum out of the two of them . 

```C++
#include <vector>
#include <algorithm> // for min

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        
        // 1. Create the MEMO table
        // Size is n + 1 because we need to reach step 'n' (the top)
        // Initialize with -1 to represent "not calculated yet"
        vector<int> memo(n + 1, -1);

        return solve(cost, n, memo);
    }

private:
    // 2. Pass memo by REFERENCE (&memo) so we share the same cache
    int solve(vector<int>& cost, int n, vector<int>& memo) {
        
        // Base Cases
        if (n == 2) return min(cost[0],cost[1]);
        if (n == 1) return 0;

        // 3. CHECK: Have we solved this sub-problem already?
        if (memo[n] != -1) {
            return memo[n];
        }

        // Recursive Step:
        int oneStep = solve(cost, n - 1, memo) + cost[n - 1];
        int twoStep = solve(cost, n - 2, memo) + cost[n - 2];

        // 4. STORE: Save the result in the memo table before returning
        memo[n] = min(oneStep, twoStep);
        
        return memo[n];
    }
};
```