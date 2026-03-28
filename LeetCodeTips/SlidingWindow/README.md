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


## Permutation in String

- Note : The max number of characters is 26 ! (given that the chars are simple or capital)

- Find the permutation of s1 substring inside the s2 . 

1. first create vectors (or hashmaps) storing counts of the chars in s1 and in the same time ... check the count of the starting window in the s2 string as well . 
2. now using a while or for loop ... slide the window 
3. when sliding the window ... add the update the count with right side char and also while removing the left side char . 
4. If it is equal boom return true !

```C++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) {
            return false;
        }

        vector<int> s1Count(26, 0);
        vector<int> s2Count(26, 0);
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }

        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1Count[i] == s2Count[i]) {
                matches++;
            }
        }

        int l = 0;
        for (int r = s1.length(); r < s2.length(); r++) {
            if (matches == 26) {
                return true;
            }

            int index = s2[r] - 'a';
            s2Count[index]++;
            if (s1Count[index] == s2Count[index]) {
                matches++;
            } else if (s1Count[index] + 1 == s2Count[index]) {
                matches--;
            }

            index = s2[l] - 'a';
            s2Count[index]--;
            if (s1Count[index] == s2Count[index]) {
                matches++;
            } else if (s1Count[index] - 1 == s2Count[index]) {
                matches--;
            }
            l++;
        }
        return matches == 26;
    }
};
```

## Minimum Window Substring

- _Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string ""._

_The testcases will be generated such that the answer is unique._

- The intuitive way is to take two hashmaps and see if they are equal each time (hash maps of char counts ...)
- Rather me make two integers and they represent the difference of characters from what the answer has rn and what the answer needs to have . 
```C++
class Solution {
public:
    string minWindow(string s, string t) {

        if (t.empty()) return "";

        unordered_map<char,int> countT , window ; 

        for (char c : t){
            countT[c]++;
        }

        int have = 0;
        int need = countT.size();
        pair<int,int> res = {-1,-1};
        int resLen = INT_MAX;
        int l = 0;

        for (int r = 0 ; r< s.length(); r++){
            char c = s[r];
            window[c]++;

            if (countT.count(c) && window[c]==countT[c]) have++;

            while (have == need){
                if ((r-l+1)<resLen){
                    resLen = r-l +1;
                    res = {l,r};
                }

                window[s[l]]--;
                if (countT.count(s[l]) && window[s[l]] < countT[s[l]]){
                    have--;
                }

                l++;
            }
        }


        return resLen == INT_MAX ? "" : s.substr(res.first , resLen);



        
    }
};
```