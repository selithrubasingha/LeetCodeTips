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