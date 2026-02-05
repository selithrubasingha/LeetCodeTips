## Best Time to Buy and Sell Stock

- You basically need to Buy the stock at the lowest point in the array . and Sell it at the highest point in the array while traversing from left to right . 

1. While traversing through the array , maintain a variable storing the current minimum value .
2. while traversing through the array with r pointer , if the the value at the index in larger than the min , check if it's larger than the max . if so update the max

```python
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        l, r = 0, 1
        maxP = 0

        while r < len(prices):
            if prices[l] < prices[r]:
                profit = prices[r] - prices[l]
                maxP = max(maxP, profit)
            else:
                l = r
            r += 1
        return maxP
```


## Longest Substring Without Repeating Characters

- findin the longest substring without duplicates ...

1. we get the l and r pointers ... r should increment everytime in the loop 
2. store the chars within l-r inside a set . 
3. check if the next value in the r index is in the set ... if it is update the l ine=dex so that char in r index is removed . 

```Python
while s[r] in charSet:
                charSet.remove(s[l])
                l += 1
```
4. Keep track of the max length with some variable and update it with every loop . 

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> charSet;
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            while (charSet.find(s[r]) != charSet.end()) {
                charSet.erase(s[l]);
                l++;
            }
            charSet.insert(s[r]);
            res = max(res, r - l + 1);
        }
        return res;
    }
};
``

