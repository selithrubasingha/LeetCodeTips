## Contains Duplicate 

- Simple question to efficiently if there is a duplicate in the array 

Hint : Use a set ! otherwise known as a unordered_set in c++ 

```C++
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> map ;

        int n = nums.size();

        for (int i = 0 ; i< n ; i++ ){
            if (map.contains(nums[i])) return true;

            map.insert(nums[i]);
        }

        return false;
        
    }
};

```

## Valid Anagram

- Find if the two words are anagrams .

**The Most Simple Way :** sort the two words and return if they are equal. 

```Python
return sorted(s) == sorted(t)
```

**The Cool Way :** Use 2 hashmaps to get the char couunt and see if they are equal 

```C++
class Solution {
public:
    bool isAnagram(string s, string t) {

        if (s.length() != t.length()) return false;

        unordered_map<char , int > sCount ; 
        unordered_map<char , int > tCount ;

        int n = s.length();
        for (int i = 0; i< n ; i++ ){
            sCount[s[i]]++;
            tCount[t[i]]++;
        } 

        return sCount == tCount;
        
    }
};
```

## Two Sum 

- I mean this is the most popular problem on leet code , does this question even need and explanation ?

- Use a hashmap and take the `diff` and see if it is in the map . 


```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        unordered_map<int,int> map ; 

        int n = nums.size();

        for (int i = 0 ; i < n ; i++){
            int diff = target - nums[i];

            if (map.contains(diff)){
                return {map[diff],i};
            }

            map[nums[i]] = i ; 
        }

        return {};


        
    }
};
```

## Group Anagram 

- Given an array of strings strs, group all anagrams together into sublists. You may return the output in any order.

**Hint :** You will need to use a hashmap , normally we use the string as the key and as the value , the count of chars ... But htis time we reverse it ! The strings are the values and vice versa , By doing this this we can group the anagrams together ! The power of the hasmap is unmatched . 


```C++ 
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        
        unordered_map<string,vector<string>> res ; 

        for (const auto& s : strs){
            vector<int> count(26,0);
            for (char c : s){
                count[c-'a']++;
            }

            string key = to_string(count[0]);

            for (int i = 1 ; i <26 ; i++){
                key += ','+to_string(count[i]);
            }

            res[key].push_back(s);
        }

        vector<vector<string>> result ; 
        for (const auto& pair : res){
            result.push_back(pair.second);
        }

        return result ; 
        
    }
};
```