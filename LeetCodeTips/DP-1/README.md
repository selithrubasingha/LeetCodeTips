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

## Decode Ways

* A message containing letters from `A-Z` is encoded into numbers using the mapping: `'A' -> "1", 'B' -> "2", ... 'Z' -> "26"`.
* Given a string of digits, return the total number of ways to decode it.

**How to Think:**

This is almost exactly like **Climbing Stairs**!
In Climbing Stairs, you can take 1 step or 2 steps.
In Decode Ways, you can take **1 digit** or **2 digits**.

**The Catch:**
Unlike stairs, not every step is allowed.

1. **One Digit:** You can take 1 digit *only* if it is NOT '0' (Mappings start at 1).
2. **Two Digits:** You can take 2 digits *only* if they form a number between 10 and 26.

**Recursive Logic:**
If I am at index `i`:

* `ways(i)` = `ways(i+1)` (if `s[i]` is valid) + `ways(i+2)` (if `s[i...i+1]` is valid).

```c++
class Solution {
public:
    int numDecodings(string s) {
        vector<int> memo(s.size(), -1);
        return solve(s, 0, memo);
    }

private:
    int solve(string& s, int i, vector<int>& memo) {
        // Base Case 1: If we reached the end, we found 1 valid path
        if (i == s.size()) return 1;

        // Base Case 2: If current char is '0', this path is invalid (dead end)
        if (s[i] == '0') return 0;

        // CHECK MEMO
        if (memo[i] != -1) return memo[i];

        // Option A: Take 1 digit (Always valid here since we passed the '0' check)
        int res = solve(s, i + 1, memo);

        // Option B: Take 2 digits (Check if it's between 10 and 26)
        if (i + 1 < s.size()) {
            if (s[i] == '1' || (s[i] == '2' && s[i+1] <= '6')) {
                res += solve(s, i + 2, memo);
            }
        }

        return memo[i] = res;
    }
};

```

**Key Takeaway:**
Always check for `'0'` first! In this problem, `'0'` is a trap. It cannot stand alone, so if you encounter it at the start of your current chunk, that path returns 0 immediately.


## Coin Change 

- Now THIS is some real recursive problems !
- You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.
Return the fewest number of coins that you need to make up the exact target amount. If it is impossible to make up the amount, return -1.
You may assume that you have an unlimited number of each coin.


        In every recursive step you substract and get a new target ... if target is achievable then surely , the target before it is achievable too!
        But what is the base case ?? When we substract if  we get a 0 , that means that The target is achievable ! we return 1 or true . if the target becomes negative , that means the target is non achievable and we should return 0 or false . 

```C++
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Create a memo table of size amount + 1.
        // We initialize with -2 to represent "not visited yet".
        // We cannot use -1 because -1 is a valid result (meaning "impossible").
        vector<int> memo(amount + 1, -2);
        
        return solve(coins, amount, memo);
    }

private:
    int solve(vector<int>& coins, int rem, vector<int>& memo) {
        // 1. Base Cases
        if (rem < 0) return -1;
        if (rem == 0) return 0;

        // 2. Check Memo: If we've seen this 'rem' before, return the stored value.
        if (memo[rem] != -2) {
            return memo[rem];
        }

        int ans = INT_MAX;

        for (int c : coins) {
            int res = solve(coins, rem - c, memo);

            if (res >= 0) {
                ans = min(ans, res + 1);
            }
        }

        // 3. Store Result in Memo before returning
        // If ans is still INT_MAX, record -1 (impossible), otherwise record ans
        memo[rem] = (ans == INT_MAX) ? -1 : ans;
        
        return memo[rem];
    }
};
```

## Word Break

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

eg:-

**Input:** s = "leetcode", wordDict = ["leet","code"]

**Output:** true

**Explanation:** Return true because "leetcode" can be segmented as "leet code"

**Thinking Pattern** : This problem similar to decode ways considering the fact that we take an `i` pointer and drag  it through the string untill the pointer reaches the end . 

```C++
class Solution {
    // Memoization table: Stores results for each index 'i'
    // -1: Unknown, 0: False, 1: True
    vector<int> memo; 

public:
    bool solve(string& s, vector<string>& wordDict, int i) {
        // Base Case: Reached the end successfully
        if (i == s.length()) return true;
        
        // MEMO CHECK: If we already know the answer for index 'i', return it immediately.
        if (memo[i] != -1) return memo[i];

        for (string& w : wordDict) {
            int len = w.length();
            
            // Check bounds and match efficiently
            if (i + len <= s.length() && s.substr(i, len) == w) {
                
                // Recursive call
                if (solve(s, wordDict, i + len)) {
                    // If we found a valid path, mark this index as TRUE (1)
                    return memo[i] = 1; 
                }
            }
        }

        // If we tried all words and none worked, mark this index as FALSE (0)
        return memo[i] = 0;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        // Initialize memo table with -1 (size is string length)
        memo.assign(s.length(), -1);
        
        // Start recursion from index 0
        return solve(s, wordDict, 0) == 1;
    }
};
```

- Notice how we make substrings in c++ , and also the bound checking logic before the recursive step . 