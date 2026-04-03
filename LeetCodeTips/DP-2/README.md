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

