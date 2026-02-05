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
```

## Longest Repeating Character Replacement

- You are given the ability to change the chars K times ... to create the longest repeating character sequence . But what is the intuition ?

1.  You see , keep a count of the chars in the substring , and instead of the char with the largest count , 
2.  Then get the sum of all the other counts , if this sum <= k times . your good to go and change . 
3.  but if sum is larger then it is time to imcrement the l pointer and update the count hashMap as well . 

```C++
class Solution {
public:
    int characterReplacement(std::string s, int k) {
        int res = 0;
        unordered_set<char> charSet(s.begin(), s.end());

        for (char c : charSet) {
            int count = 0, l = 0;
            for (int r = 0; r < s.size(); r++) {
                if (s[r] == c) {
                    count++;
                }

                while ((r - l + 1) - count > k) {
                    if (s[l] == c) {
                        count--;
                    }
                    l++;
                }

                res = std::max(res, r - l + 1);
            }
        }
        return res;
    }
};
```