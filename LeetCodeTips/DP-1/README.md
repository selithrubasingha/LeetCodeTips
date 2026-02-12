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

## House Robber

- You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

- Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

**How to Think :**

    So the robber can't rob adjacent houses , He could rob non adjacent house BUT it's NOT LIMITED to robbing houses by skipping one every time . he could skip two times too . 

    That is why we need to solve it recursively . 

    Say the robber is at a house ... He could either rob it or skip it . 

    1. If the robber skipped it (house n) : The total houses robbed is upto n-1 . 
    2. If the robber Robs it , He couldn't have robbed n-1 house . Which means the cost of house[n] should be added to sum of houses robbed upto hous[n-2].
   

```C++
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // 1. Create the memo table
        // Size is n + 1 because we are solving for "first n houses"
        vector<int> memo(n + 1, -1);
        
        return solve(nums, n, memo);
    }

private:
    int solve(vector<int>& nums, int n, vector<int>& memo) {
        // Base Cases
        if (n <= 0) return 0; // If 0 houses, 0 money. Handles the (n-2) case safely.
        if (n == 1) return nums[0]; // If 1 house, rob it.

        // 2. CHECK: Have we calculated this 'n' before?
        if (memo[n] != -1) {
            return memo[n];
        }

        // Logic:
        // Option A: Rob current house (nums[n-1]) + loot from (n-2) remaining houses
        int robCurrent = nums[n - 1] + solve(nums, n - 2, memo);
        
        // Option B: Skip current house + loot from (n-1) remaining houses
        int skipCurrent = solve(nums, n - 1, memo);

        // 3. STORE: Save the max result
        return memo[n] = max(robCurrent, skipCurrent);
    }
};
```

* Notice in the code , when you n=input int n  , we're actually looking at the house n-1 ! That is cause of the indexing pattern in this method . We could change it if you like , but I am too lazy for that . 