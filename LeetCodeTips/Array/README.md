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

## Top K frequent elements 

Given an integer array nums and an integer k, return the k most frequent elements within the array.

**Hint :** Use the legendary bucket sort technique ! instead of number as key and count as value .... why not make it count as key a list of numbers which have the same count as the values ? Basically the same idea as in the Group Anagrams in a way . 

``` C++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        int n = nums.size();
        unordered_map<int,int> count ; 
        vector<vector<int>> freq(nums.size() + 1);

        for (int n  : nums){
            count[n]++;
        }

        for (const auto& pair : count){
            freq[pair.second].push_back(pair.first);

        }

        vector<int> res;

        for (int i = n ; i>=0 ; i--){
            for (int j : freq[i]){
                res.push_back(j);
                
                if (res.size()==k) return res ; 
            }
        }

        return res;

```

- For the `freq` why didn't we use a unordered_map ? because it is unordered ! Here we use a vector which is indexed (and that is useful here) to get certain values . 
- Maybe for some other problems , two unordered_maps can be used as well ...

## Product of array except self 

- Given an integer array nums, return an array output where output[i] is the product of all the elements of nums except nums[i].

Each product is guaranteed to fit in a 32-bit integer.

Follow-up: Could you solve it in 
O(n) time without using the division operation?


**Hint :** This is where you should use the technique of prefix and suffix ! you maintain memory of the arraya before each reveiwing element (kind of ).

- Of course if we were to use division this would be a piece of cake  !

```C++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> preffix(n,1);
        vector<int> suffix(n,1);

        int p = nums[0];

        for (int i = 1 ; i< n ; i++){
            preffix[i] = p ; 
            p*= nums[i];

        }

        int s = nums[n-1];

        for (int i = n-2 ; i>=0 ;i--){
            suffix[i] = s;
            s*= nums[i];
        }

        vector<int> ans  ; 

        for (int i = 0 ; i <n ; i++){
            ans.push_back(preffix[i]*suffix[i]);
        }

        return ans;
        
    }
};
```
