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