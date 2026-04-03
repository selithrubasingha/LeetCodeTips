# 2-Dimensional dynamic programming 

- The thing with 2D dp is that ... there are 2 variables in each dp subproblem .
- in recursion , there are two variables that are being changed in the stack.
- sO if we use recursion , we better use a 2D matrix for memoization !
- Or if we use iterative DFS , we need to use a 2D matrix dp array . 

## Unique Paths

_There is an m x n grid where you are allowed to move either down or to the right at any point in time.Given the two integers m and n, return the number of possible unique paths that can be taken from the top-left corner of the grid `(grid[0][0])` to the bottom-right corner `(grid[m - 1][n - 1])`.You may assume the output will fit in a 32-bit integer._

- We we iterate through the dp matrix  , right to left , down to top ,
- `dp[i][j] = dp[i+1][j]+dp[i][j+1];` This is the subproblem case , the answer is the sum of the paths we get if we go right AND if we go down , 
- Note how the base case is `1` for the last column and last row . 

```C++
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,1));

        for (int i = m-2 ; i>=0 ; i--){
            for (int j = n-2 ; j>=0; j--){
                dp[i][j] = dp[i+1][j]+dp[i][j+1];
            }
        }

        return dp[0][0];
        
    }
};
```


## Longest Common Subsequence
 
- When we go through , the  dp , if the the char is equal , look at
the top left num and add 1 to it . 
- if the chars ain't similar , just get the max from left or from top .

```C++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();

        vector<vector<int>> dp(m+1,vector<int> (n+1,0));

        for (int i= 0; i<m; i++){
            for (int j=0; j<n ; j++){
                if (text1[i]==text2[j]){
                    dp[i+1][j+1]  = 1+ dp[i][j];
                }else{
                    dp[i+1][j+1] = max(dp[i][j+1] , dp[i+1][j]);
                }
            }
        }

        return dp[m][n];
        
    }
};
```

## Best Time to Buy and Sell Stock with Cooldown

- What makes this question interesting is that , this clearly shows the two variable thiing , and one of them is a boolean ! . s o depending on that boolean , the logic inside  the recusion may need to be changed . (using a if statement maybe)

```C++
class Solution {
public:
    unordered_map<string, int> dp;


    int maxProfit(vector<int>& prices) {
        return solve(0 , true ,prices);
        
    }

    int solve(int i , bool buying,vector<int>& prices){
        int n = prices.size();

        if (i>=n) return 0;

        string key = to_string(i) + "-" + to_string(buying);
        if (dp.find(key) != dp.end()) {
            return dp[key];
        }


        int cooldown = solve(i+1 , buying , prices);
        if (buying){
            int buy = solve(i+1, false , prices) - prices[i];
            dp[key] = max(cooldown , buy);
        }else{
            int sell = solve(i+2 , true , prices)+ prices[i];
            dp[key] = max(cooldown , sell);
        }

        return dp[key];


    }
};
```

## Coin Change II

- There are a few variations of the legendary coin change problem 

1. can we get answer ?(ans is a `boolean`) [coins can be uses ANY number of times]
2. can we get answer ?(ans is a `boolean`) [each coin can be used  only one time]
3. How many answer can we get ? (ans is an `int`) [coins can be uses ANY number of times]
4. How many answer can we get ? (ans is an `int`) [each coin can be used  only one time]

- Coin Change II is actually the 3rd one .

```C++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        vector<vector<int>>  memo(amount+1 ,vector<int> (n+1,-1));

        return solve(amount , coins , 0 , memo);
        
    }

    int solve(int amount, vector<int>& coins,int startIndex , vector<vector<int>> & memo){
        int n = coins.size();

        if (amount==0) return 1;
        if (amount<=0) return 0;

        if (memo[amount][startIndex]!=-1) return memo[amount][startIndex];

        int total = 0 ;

        for (int i = startIndex ; i < n ; i++){
            total += solve(amount-coins[i], coins , i , memo);

        }

        memo[amount][startIndex] = total;

        return total;
    }
};

```

if you were asked the 4th variation of the question . change `total += solve(amount-coins[i], coins , i , memo)` to `total += solve(amount-coins[i], coins , i+1 , memo)`.

## Target Sum

- The actual logic is pretty simple , the thing is the memoization . i here the variabel `target` becomes negative , so we need to add some kind of offset to make all the answers positive , preferably the sum of the nums in teh vector !

```C++

class Solution {
    vector<vector<int>> dp;
    int totalSum;

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        totalSum = accumulate(nums.begin(), nums.end(), 0);
        dp = vector<vector<int>>(nums.size(), vector<int>(2 * totalSum + 1, INT_MIN));
        return backtrack(0, 0, nums, target);
    }

    int backtrack(int i, int total, vector<int>& nums, int target) {
        if (i == nums.size()) {
            return total == target;
        }
        if (dp[i][total + totalSum] != INT_MIN) {
            return dp[i][total + totalSum];
        }
        dp[i][total + totalSum] = backtrack(i + 1, total + nums[i], nums, target) +
                                  backtrack(i + 1, total - nums[i], nums, target);
        return dp[i][total + totalSum];
    }
};
```

## Interleaving string

- This is also a list , 0 -> n kindof problem . Meaning we solve the subproblems by incementing the index 
- well 2 INDEXES in this cause it's a 2D dp problem . 

- Basically the problem the problem is asking whether you can split s1 and s2 into pieces and stitch it up to make s3 .(The order of the pieces should not change )

```C++
class Solution {
    vector<vector<int>> dp;

public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length();
        if (m + n != s3.length()) return false;
        dp = vector<vector<int>>(m + 1, vector<int>(n + 1, -1));
        return dfs(0, 0, 0, s1, s2, s3);
    }

    bool dfs(int i, int j, int k, string& s1, string& s2, string& s3) {
        if (k == s3.length()) {
            return (i == s1.length()) && (j == s2.length());
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        bool res = false;
        if (i < s1.length() && s1[i] == s3[k]) {
            res = dfs(i + 1, j, k + 1, s1, s2, s3);
        }
        if ( !res && j < s2.length() && s2[j] == s3[k]) {
            res = dfs(i, j + 1, k + 1, s1, s2, s3);
        }

        dp[i][j] = res;
        return res;
    }
};
```

- Notice that the `if ( !res && j < s2.length() && s2[j] == s3[k]) {
            res = dfs(i, j + 1, k + 1, s1, s2, s3);
        }` the `!res` is important ! 


## Longest Increasing Path in Matrix

- In the unique paths problem ... we went down or right , BUT IN THIS QUESTION , we go all 4 directions .

- we keep a `prevVal` variable to store what the previous value in the recursive call is , if the `curVal > prevVal` we consider it added to the length of the path we are finding . 

- Also note that in the code , we call the recursive function for ALL the values ! although the memoization helps with the time complexity  .

```C++
class Solution {
public:
    vector<vector<int>> dp;

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int ROWS = matrix.size(), COLS = matrix[0].size();
        dp = vector<vector<int>>(ROWS, vector<int>(COLS, -1));
        int LIP = 0;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                LIP = max(LIP, solve(matrix, r, c, INT_MIN));
            }
        }
        return LIP;
        
    }

    int solve(vector<vector<int>>& matrix, int i , int j , int prevVal){
        int n = matrix.size();
        int m = matrix[0].size();
        if (i>=n || i<0 || j>=m || j<0 || matrix[i][j] <= prevVal) return 0;

        if (dp[i][j]!=-1) return dp[i][j];

        int res = 1;
        res = max(res , 1+ solve(matrix , i+1,j,matrix[i][j]));
        res = max(res , 1+ solve(matrix , i-1,j,matrix[i][j]));
        res = max(res , 1+ solve(matrix , i,j+1,matrix[i][j]));
        res = max(res , 1+ solve(matrix , i,j-1,matrix[i][j]));

        dp[i][j] = res;
        return res;
    }
};
```
