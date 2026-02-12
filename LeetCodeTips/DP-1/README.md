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

## House Robber 2

* Same as House Robber 1 but the cache is that , the houses are arranged in a FULL CIRCLE ! How do we solve it ?

**Thinking:**
    The difference is that now the first and the last houses are interconnected , if you rob the first house , You can't rob the last house and vice versa . 

    So how do we solve this ? We use the same solve function for House Robber 1 . and do it for nums[1:] and nums[:-2] ! and the the maximum of it . That way we can get the answer of the houses without robbing both first and last houses . 


```C++
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // 1. Create the memo table
        // Size is n + 1 because we are solving for "first n houses"
        vector<int> memo1(n + 1, -1);
        vector<int> memo2(n + 1, -1);

        if (nums.size()<=2) return solve(nums, n, memo1);

        vector<int> sub(nums.begin() + 1, nums.end());
        vector<int> sub2(nums.begin(), nums.end() - 1);
        
        return max(solve(sub, n-1, memo1),solve(sub2, n-1, memo2));
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


## Longest Palindromic Substring

* When talking about palindromes , the easiest way to find a find a palindrome substring is to select an char and expland from the left and right !!!
* what about for even palindromes , choose 2 chars at first and expand from the left and right . 

```C++
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        string res = "";
        int resLen = 0;
        for (int i=0; i<n; i++){
            int l = i;
            int r = i ;

        //odd_palindromes
            while (l>=0 && r<n && s[l]==s[r]){
                int pal_len = r-l+1;

                if (resLen<pal_len){
                    res = s.substr(l,pal_len);
                    resLen = pal_len;
                }

                l--;
                r++;

            }


            l=i;
            r=i+1;

            //even_palindromes
            while (l>=0 && r<n && s[l]==s[r]){
                int pal_len = r-l+1;

                if (resLen<pal_len){
                    res = s.substr(l,pal_len);
                    resLen = pal_len;
                }

                l--;
                r++;

            }

        }

        return res;
        
    }
};
```

This is NOT the recursive method but this actually the most efficient method for palindromes . 

for the sake of completion here is how to do it recursively . 

```C++
#include <vector>
#include <string>
#include <algorithm>
#include <cstring> // for memset

using namespace std;

class Solution {
public:
    // Memo table: -1 = uncalculated, 0 = false, 1 = true
    // We use 1001 based on typical constraint (s.length <= 1000)
    int memo[1001][1001]; 

    string longestPalindrome(string s) {
        int n = s.length();
        if (n == 0) return "";
        
        // Initialize memo table with -1
        memset(memo, -1, sizeof(memo));
        
        int maxLen = 0;
        int startIdx = 0;

        // Iterate through all possible substrings s[i...j]
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                // If s[i...j] is a palindrome AND it's longer than current max
                if (solve(s, i, j) == 1) {
                    if (j - i + 1 > maxLen) {
                        maxLen = j - i + 1;
                        startIdx = i;
                    }
                }
            }
        }

        return s.substr(startIdx, maxLen);
    }

private:
    // Helper function: Returns 1 if s[i...j] is a palindrome, 0 otherwise
    int solve(string& s, int i, int j) {
        // Base Case 1: If i >= j, we have crossed over or are at the same char.
        // Single char or empty string is always a palindrome.
        if (i >= j) return 1;

        // Base Case 2: Check Memo
        if (memo[i][j] != -1) return memo[i][j];

        // Recursive Step:
        // Match outer chars AND check if inner substring is palindrome
        if (s[i] == s[j]) {
            memo[i][j] = solve(s, i + 1, j - 1);
        } else {
            memo[i][j] = 0; // Not a match, so not a palindrome
        }

        return memo[i][j];
    }
};
```

## Palindromic Substrings

* This is the same as longest palindromic substring , But the logic is changed a bit . You don't have to keep count of the longest substring ... BUT everytime you do l--;r++; you should increase the count++;

```C++
class Solution {
public:
    int memo[1001][1001]; 

    // Recursive function to check if s[i...j] is a palindrome
    bool solve(string &s, int i, int j) {
        // Base case: If pointers cross or meet, it's a valid palindrome
        // (This handles length 0 or 1 centers)
        if (i >= j) return true;

        // Check if we already calculated this state
        if (memo[i][j] != -1) return memo[i][j];

        // Logic: Ends must match AND inner part must be palindrome
        if (s[i] == s[j]) {
            return memo[i][j] = solve(s, i + 1, j - 1);
        }

        return memo[i][j] = false;
    }
    int countSubstrings(string s) {

        int n = s.length();
        memset(memo, -1, sizeof(memo));

        int count = 0 ;

        for (int i = 0; i<n ; i++){
            for (int j =i; j<n ; j++){
                bool isPalin = solve(s , i , j );

                if (isPalin){
                    count++;
                }

            }
        }

        return count ; 
        


        
    }
};
```

